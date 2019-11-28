#include "GameServer.h"
#include "Controller.h"
#include "../to_remove_or_modify/LevelBuilder.h"
#include "../logger/Logger.h"
#include "../logger/LogManager.h"
#include "../CLIAparser/CLIArgumentParser.h"
#include "../XMLparser/xmlparser.h"
#include <unistd.h>

#include "../net/messaging/IDManager.h"
#include "../image/ImageUtils.h"
#include "../net/messaging/User.h"
#include "../enumerates/Color.h"

#include <iostream>
#include <utility>

bool GameServer::hasInstance = false;

void GameServer::start() {
    LogManager::logInfo("[GAME]: Se inicia Game");

    initController();
    startServer();          //1 thread de listen de conexiones nuevas y 4 threads por cliente nuevo

    initWaitingScreen();
    waitUnitAllPlayersConnected();

    initGameModel();
    gameLoop();

    closeServer();          //se cierra el thread se server y (previamente se cierran los 4 threads child)

    LogManager::logInfo("[GAME]: Juego terminado");
    LogManager::logInfo("=======================================");

    cout << "everything endded up nicely :D" << endl;
}

//GAME LOOP
//=========================================================================================

void GameServer::gameLoop(){

    while (isOn() && levelBuilder->hasNextLevel() && notAllPlayersDisconnected()) {

        levelBuilder->loadNext();
        LogManager::logInfo("=======================================");
        LogManager::logInfo("[GAME]: se inicia game loop de este nivel");

        while (isOn() && !levelBuilder->levelFinished() && notAllPlayersDisconnected()) {
            update();
            sendUpdate();
            usleep(SLEEP_TIME);
        }
        LogManager::logInfo("[GAME]: Nivel terminado");
        LogManager::logInfo("=======================================");
    }
    on = false;
    server->stopListening();
}

void GameServer::update() {
    manager->update();
    controller->clearAllInputs();
}

void GameServer::sendUpdate() {
    controller->sendUpdate(manager->generateSendables(), server);
}

//API
//=========================================================================================

std::string GameServer::validateLogin(const std::string& user,const std::string& pass, int userId){


    if (credentialsAreValid(user,pass)){
        if (userAlreadyLoggedIn(user)){
            if (userIsDisconnected(user)){
                return processReconectionAndEmitSuccesMessage(user,userId);
            }
            else{
                return controller->getAlreadyLoggedInMessage();
            }
        }
        else{
            if (serverFull()){
                return controller->getServerFullMessage();
            }
            else{
                return processConectionAndEmitSuccesMessage(user, pass, userId);
            }
        }
    }
    else{
        return controller->getInvalidCredentialMessage();
    }
}

void GameServer::addNewIDToGame(int id) {
    IDManager::getInstance().addNewIdPlayer(id);
}

void GameServer::reemplazePreviousIDWith(int oldID, int newID) {
    IDManager::getInstance().reemplaze(oldID, newID);
}

int GameServer::getCurrentLevelWidth(){
    return levelBuilder->getCurrentLevelWidth();
}

void GameServer::reciveNewInput(tuple<Action,int> input){
    return controller->setInput(input);
}

bool GameServer::isActive(){
    return hasInstance;
}

bool GameServer::playersCanMove(){
    return loggedPlayersPassByUser.size() == maxPlayers;
}

bool GameServer::isIDLogged(int ID){
    return loggedPlayersUserByID.count( ID );
}

void GameServer::sendWaitingScreen() {
    controller->sendUpdate(waitingScreenContainer,server);
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

    while ((loggedPlayersPassByUser.size() != maxPlayers) ||
            (!disconectedPlayers.empty())){
        sendWaitingScreen();
        usleep(SLEEP_TIME);
    }
}

bool GameServer::notAllPlayersDisconnected(){
    return disconectedPlayers.size() < maxPlayers;
}

void GameServer::connectionLostWith(int id){

    if (loggedPlayersUserByID.count(id)){

        string name = loggedPlayersUserByID.at(id).name;
        disconectedPlayers.insert({name,id});
    }
    if (manager != nullptr){
        manager->disconectPlayerByID(id);
    }
}

//CONTROLLER RELATED
//=========================================================================================

void GameServer::initController() {
    controller = new Controller(this);
    LogManager::logDebug("[INIT]: inicializado Controller");
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

    return controller->getSuccesfullLoginMessage(user.color, id);
}

string GameServer::processReconectionAndEmitSuccesMessage(const string& name, int newID){

    int oldID = loggedPlayersIDbyUser.at(name);
    User user = loggedPlayersUserByID.at(oldID);

    loggedPlayersUserByID.erase(oldID);
    loggedPlayersUserByID.insert({newID,user});

    loggedPlayersIDbyUser.at(user.name) = newID;

    reemplazePreviousIDWith(oldID, newID);

    disconectedPlayers.erase(user.name);
    if (manager != nullptr){
        manager->reconectPlayerByID(oldID, newID);
    }

    return controller->getSuccesfullLoginMessage(user.color,newID);
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
void GameServer::initWaitingScreen() {
    string path = "resources/sprites/waitingScreens/waiting_for_your_teammates.png";

    ImageSize imageSize = ImageUtils::getImageSize(path);
    int imageWidth = imageSize.width;
    int imageHeight = imageSize.height;

    int screenWidth = config->screenResolution.width;
    int screenHeight = config->screenResolution.height;

    Rect src = {0,0,imageWidth,imageHeight};
    Rect dst = {0,0,screenWidth,screenHeight};

    waitingScreenRenderable = new Renderable(path, src, dst, false);
    waitingScreenContainer = new list<Renderable*>();
    waitingScreenContainer->push_back(waitingScreenRenderable);
}

void GameServer::initGameModel() {
    initECSManager();
    initLevelBuilder();
    LogManager::logDebug("[INIT]: inicializado Manager");
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

void GameServer::initECSManager() {
    this->manager = new Manager();
}

void GameServer::initLevelBuilder() {
    this->levelBuilder = new LevelBuilder(manager, config);
}

//DESTROY
//=========================================================================================

void GameServer::destroy() {
    if (!waitingScreenContainer->empty()){
        delete(waitingScreenContainer->front());
    }
    waitingScreenContainer->pop_front();
    waitingScreenContainer = nullptr;
    delete(waitingScreenRenderable);
    waitingScreenRenderable = nullptr;
    delete(server);
    server = nullptr;
    delete(levelBuilder);
    levelBuilder = nullptr;
    delete(manager);
    manager = nullptr;
    baseClassFreeMemory();
    LogManager::logDebug("Memoria de Game Server liberada");
}