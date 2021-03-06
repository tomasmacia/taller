#include "GameServer.h"
#include "Controller.h"
#include "LevelBuilder.h"

#include <ctime>
#include <iostream>

bool GameServer::hasInstance = false;

void GameServer::start() {
    LogManager::logInfo("[GAME]: Se inicia Game");

    initController();
    startServer();          //1 thread de listen de conexiones nuevas y 4 threads por cliente nuevo
    initSceneDirector();

    waitUnitAllPlayersConnected();

    initGameModel();
    gameLoop();

    closeServer();          //se cierra el thread se server getY (previamente se cierran los 4 threads child)

    LogManager::logInfo("[GAME]: Juego terminado");
    LogManager::logInfo("=======================================");

    cout << "everything endded up nicely :D" << endl;
}

//GAME LOOP
//=========================================================================================

void GameServer::gameLoop(){

    sendGameStartedMessage();
    while (isOn() && levelBuilder->hasNextLevel() && thereIsAtLeastOnePlayerAliveAndConnected()) { //levels loop

        levelBuilder->loadNext();
        LogManager::logInfo("=======================================");
        LogManager::logInfo("[GAME]: se inicia game loop de este nivel");

        while (isOn() && !levelBuilder->levelFinished() && thereIsAtLeastOnePlayerAliveAndConnected()) { //game loop
            update();
            sendUpdate();
            usleep(SLEEP_TIME);
        }
        if (thereIsAtLeastOnePlayerAliveAndConnected()) { //score screen
            sceneDirector->initScoreScreen(entityManager->getPlayers(),loggedPlayersUserByID);
            sceneDirector->sendScoreScreen(server);
             usleep(WAIT_TIME);
        }
        LogManager::logInfo("[GAME]: Nivel terminado");
        LogManager::logInfo("=======================================");
    }
    if (allDied()){
        sceneDirector->initScoreScreen(entityManager->getPlayers(),loggedPlayersUserByID);
        sceneDirector->sendScoreScreen(server);
        usleep(WAIT_TIME);
    }

    if (notAllPlayersDisconnected() ) { //end screen
        sendEndMessage();
        sceneDirector->initEndOfGameScreen();

        for (int i = 0; i < END_SCREEN_SEND_AMOUNT; i++){ //esto es porque la ser de lo ultimo que manda el server hay que mandarlo varias veces para que llegue
            sceneDirector->sendEndOfGameScreen(server);
        }
    }
    end();
    server->stopListening();
}

void GameServer::update() {
    entityManager->update();
    levelBuilder->update();
}

void GameServer::sendUpdate() {
    auto* sendables = entityManager->generateSendables();

    /*
    for (auto sendable : *sendables){
        if (sendable->_soundable != nullptr){
            cout<<"Se mando a emitir: "<<sendable->_soundable->getPath()<<" ,cant total paquetes a enviar: "<<sendables->size()<<endl;
        }
    }*/

    controller->sendUpdate(sendables, server);
}

//API
//=========================================================================================

void GameServer::handleLogin(const std::string& user, const std::string& pass, int userId){

    string toSendMessage;
    //usleep(2000000);

    if (credentialsAreValid(user,pass)){
        if (userAlreadyLoggedIn(user)){
            if (userIsDisconnected(user)){
                processReconectionAndEmitSuccesMessage(user,userId);
            }
            else{
                toSendMessage = controller->getAlreadyLoggedInMessage();
                server->setToSendToSpecific(toSendMessage,userId);
            }
        }
        else{
            if (serverFull()){
                toSendMessage = controller->getServerFullMessage();
                server->setToSendToSpecific(toSendMessage,userId);
            }
            else{
                toSendMessage = processConectionAndEmitSuccesMessage(user, pass, userId);
                server->setToSendToSpecific(toSendMessage,userId);
            }
        }
    }
    else{
        toSendMessage = controller->getInvalidCredentialMessage();
        server->setToSendToSpecific(toSendMessage,userId);
    }
}

void GameServer::addNewIDToGame(int id) {
    IDManager::getInstance().addNewIdPlayer(id);
}

void GameServer::reemplazePreviousIDWith(int oldID, int newID) {
    IDManager::getInstance().reemplaze(oldID, newID);
}

void GameServer::reciveNewInput(tuple<Action,int> input){
    return entityManager->setInput(input);
}

bool GameServer::isActive(){
    return hasInstance;
}

bool GameServer::isIDLogged(int ID){
    return loggedPlayersUserByID.count( ID );
}

bool GameServer::thereIsAtLeastOnePlayerAliveAndConnected() {
    return conectedAndPlayingPlayersAmount > 0;
}

void GameServer::recibeTestModeSignal() {

    if (entityManager != nullptr){

        inTestMode = !inTestMode;

        if (inTestMode){
            entityManager->setTestMode();
            LogManager::logInfo("[GAME]: modo test activado");
        }
        else{
            entityManager->removeTestMode();
            LogManager::logInfo("[GAME]: modo test desactivado");
        }
    }

}

bool GameServer::allDied() {
    return deadPlayers.size() == maxPlayers;
}

//SERVER RELATED
//=========================================================================================
void GameServer::startServer(){
    server = new Server(this);
    server->init();
    listenConnectionsThread = std::thread(&Server::listenThread,server);
    LogManager::logInfo("[INIT]: Server inicializado");
}

void GameServer::closeServer(){
    listenConnectionsThread.join();
    server->close();
}

void GameServer::waitUnitAllPlayersConnected(){

    sceneDirector->initWaitingScreen();
    while ((loggedPlayersPassByUser.size() != maxPlayers) ||
            (!disconectedPlayers.empty())){
        sceneDirector->sendWaitingScreen(server);
        usleep(SLEEP_TIME);
    }
}

bool GameServer::notAllPlayersDisconnected(){
    return disconectedPlayers.size() < maxPlayers;
}

void GameServer::connectionLostWith(int id){

    bool logged = loggedPlayersUserByID.count(id);
    bool dead = deadPlayers.count(id);
    string name = "UNKNOWN";

    if (logged){
        name = loggedPlayersUserByID.at(id).name;
        disconectedPlayers.insert({name,id});

        if (!dead){
            conectedAndPlayingPlayersAmount --;
        }
    }
    if (entityManager != nullptr){
        entityManager->disconectPlayerByID(id);
    }
    LogManager::logInfo("[GAME]: se proceso al jugador desconectado: " + to_string(id) + " | " + name);
}

//CONTROLLER RELATED
//=========================================================================================

void GameServer::sendEndMessage() {
    controller->sendEndMessage(server);
}

void GameServer::notifyPlayerDied(int id) {
    conectedAndPlayingPlayersAmount --;
    controller->sendPlayerDiedMessage(server,id);
    deadPlayers.insert({id,loggedPlayersUserByID.at(id).name});
    LogManager::logInfo("[GAME]: se proceso al jugador muerto: " + to_string(id) + " | " + loggedPlayersUserByID.at(id).name);
}

void GameServer::sendGameStartedMessage() {
    controller->sendGameStartedMessage(server);
}


//LOGIN RELATED
//=========================================================================================
bool GameServer::serverFull(){
    return loggedPlayersPassByUser.size() == maxPlayers;
}

bool GameServer::credentialsAreValid(const string& user, const string& pass){
    return validUser(user) && validPass(user,pass);
}

bool GameServer::userAlreadyLoggedIn(const string& user){
    return userInLoggedPlayers(user);
}

bool GameServer::userIsDisconnected(const string& user){
    return IDInDisconnectedPlayers(user);
}

bool GameServer::validUser(const string& user){
    return validCredentials.find(user) != validCredentials.end();
}

bool GameServer::validPass(const string& user, const string& pass){
    return validCredentials.at(user) == pass;
}

bool GameServer::userInLoggedPlayers(const string& user){
    return loggedPlayersPassByUser.find(user) != loggedPlayersPassByUser.end();
}

bool GameServer::IDInDisconnectedPlayers(const string& user){
    return disconectedPlayers.find(user) != disconectedPlayers.end();
}

string GameServer::processConectionAndEmitSuccesMessage(const string& name, const string& pass, int id){

    User user(name,this->getNewColor());


    loggedPlayersPassByUser.insert({ user.name, pass });
    loggedPlayersUserByID.insert({ id, user });
    loggedPlayersIDbyUser.insert({user.name,id});
    addNewIDToGame(id);
    //server->client_noBlock(id);

    LogManager::logInfo("[GAME]: se proceso al jugador conectado: " + to_string(id) + " | " + user.name);
    return controller->getSuccesfullLoginMessage(user.color, id);
}

void GameServer::processReconectionAndEmitSuccesMessage(const string& name, int newID){

    int oldID = loggedPlayersIDbyUser.at(name);
    User user = loggedPlayersUserByID.at(oldID);

    loggedPlayersUserByID.erase(oldID);
    loggedPlayersUserByID.insert({newID,user});

    loggedPlayersIDbyUser.at(user.name) = newID;

    reemplazePreviousIDWith(oldID, newID);

    disconectedPlayers.erase(user.name);
    if (entityManager != nullptr){
        entityManager->reconectPlayerByID(oldID, newID);
    }

    bool dead = deadPlayers.count(oldID);

    if (dead) {
        deadPlayers.erase(oldID);
        deadPlayers.insert({newID, user.name});
    }
    else {
        conectedAndPlayingPlayersAmount++;
    }

    //server->client_noBlock(newID);
    server->setToSendToSpecific(controller->getSuccesfullLoginMessage(user.color,newID),newID);
    server->setToSendToSpecific(controller->getGameStartedMessage(),newID);
    if (dead) {
        controller->sendPlayerDiedMessage(server,newID);
    }
    LogManager::logInfo("[GAME]: se proceso al jugador reconectado: " + to_string(newID) + " | " + user.name);
}

string GameServer::getNewColor() {
    switch (currentColor){
        case BLUE:
            currentColor = RED;
            return "BLUE";
        case RED:
            currentColor = GREEN;
            return "RED";
        case GREEN:
            currentColor = YELLOW;
            return "GREEN";
        case YELLOW:
            currentColor = COLOR_UNDEFINED;
            return "YELLOW";
        case COLOR_UNDEFINED:
            LogManager::logError("[LOGIN]: tried to assign undefined color");
            return "COLOR_UNDEFINED";
    }
}


//INIT
//=========================================================================================

void GameServer::initController() {
    controller = new Controller(this);
    LogManager::logDebug("[INIT]: inicializado Controller");
}

void GameServer::initGameModel() {
    conectedAndPlayingPlayersAmount = maxPlayers;
    entityManager = initLevelBuilder();
    entityManager->setGame(this);
    LogManager::logDebug("[INIT]: inicializado EntityManager");
    LogManager::logDebug("[INIT]: inicializado LevelBuilder");
    LogManager::logInfo("[INIT]: Modelo inicializado");
}

void GameServer::init() {
    initConfig();
    loadValidCredenctials();
    maxPlayers = config->serverMaxPlayers;

    LogManager::logDebug("[INIT]: inicializado Config");
    LogManager::logDebug("[INIT]: cargado credenciales");
    LogManager::logDebug("=======================================");
}

void GameServer::loadValidCredenctials(){
    string pathToConfigFile = CLIArgumentParser::getInstance().getPathToUserCredentialsFileName();

    XMLParser xmlParser;
    Credentials *credentials = xmlParser.parseCredentials(pathToConfigFile);

    for (auto &userCredentials : credentials->users) {
        this->validCredentials.insert(std::make_pair(userCredentials.username, userCredentials.password));
    }
}

EntityManager* GameServer::initLevelBuilder() {
    this->levelBuilder = new LevelBuilder(controller, config);
    return levelBuilder->getEntityManager();
}

//DESTROY
//=========================================================================================

void GameServer::destroy() {

    delete(server);
    server = nullptr;
    delete(levelBuilder);
    levelBuilder = nullptr;
    delete(sceneDirector);
    sceneDirector = nullptr;
    baseClassFreeMemory();
    //LogManager::logDebug("Memoria de Game Server liberada");
}
