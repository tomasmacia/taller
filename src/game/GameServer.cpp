#include "GameServer.h"
#include "Controller.h"
#include "LevelBuilder.h"
#include "../LogLib/Logger.h"
#include "../LogLib/LogManager.h"
#include "../parser/CLIArgumentParser.h"
#include "../parser/xmlparser.h"

#include "IDPlayer.h"

#include <iostream>

bool GameServer::hasInstance = false;

void GameServer::start() {
    LogManager::logInfo("Se inicia Game");

    cout << validCredentials.size() << " credenciales levantadas" << endl;

    //VER DE SACAR ESTO AL FINAL
    initController();       //1 thread para escuchar teclado y la crucecita de la window
    startServer();          //1 thread de listen de conexiones nuevas y 4 threads por cliente nuevo

    waitUnitAtLeasOnePlayerConnected();

    initGameModel();
    gameLoop();

    closeServer();          //se cierra el thread se server y (previamente se cierran los 4 threads child)
    closeController();      //se cierra el thread del teclado y la crucecita de la window

    LogManager::logInfo("Juego terminado");
    LogManager::logInfo("=======================================");

    cout<<"everything endded up nicely :D"<<endl;
}

//GAME LOOP
//=========================================================================================

void GameServer::gameLoop(){

    while (isOn() && levelBuilder->hasNextLevel() && notAllPlayersDisconnected()) {
        levelBuilder->loadNext();
        LogManager::logInfo("=======================================");
        LogManager::logInfo("se inicia game loop de este nivel");
        while (isOn() && !levelBuilder->levelFinished() && notAllPlayersDisconnected()) {
            update();
            sendUpdate();
        }
        LogManager::logInfo("fin de game loop de este nivel");
        LogManager::logInfo("=======================================");
    }
}

void GameServer::update() {
    manager->update();
    controller->clearAllInputs();
}

void GameServer::sendUpdate() {
    controller->sendUpdate(manager->generateRenderables(),server);
}

//API
//=========================================================================================

std::string GameServer::validateLogin(std::string user, std::string pass, int userId){

    if (serverFull()){
        return controller->getServerFullMessage();
    }
    else{
        if (userInValidCredentials(user)){
            if (passInValidCredentials(user,pass)){
                if(userInLoggedPlayers(user)){
                    if(IDInDisconnectedPlayers(userId)){
                        return processReconectionAndEmitSuccesMessage(userId);
                    }
                    else{
                        return controller->getAlreadyLoggedInMessage();
                    }
                }
                else{
                    return processConectionAndEmitSuccesMessage(user, pass, userId);
                }
            }
            else{
                return controller->getInvalidCredentialMessage();
            }
        }
        else{
            return controller->getInvalidCredentialMessage();
        }
    }
}

void GameServer::endLevel(){
    LogManager::logInfo("Nivel terminado");
    levelBuilder->endLevel();
}

void GameServer::addNewIDToGame(int id) {
    IDPlayer::getInstance().addNewIdPlayer(id);
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
    return loggedPlayers.size() == maxPlayers;
}

//SERVER RELATED
//=========================================================================================
void GameServer::startServer(){
    server = new Server(this);
    server->init();
    listenConnectionsThread = std::thread(&Server::listenThread,server);
    LogManager::logInfo("Server inicializado");
}

void GameServer::closeServer(){
    lisentToInputForClosing.join();
}

void GameServer::waitUnitAtLeasOnePlayerConnected(){

    while (!(loggedPlayers.size() > 0)){
        continue;
    }
}

bool GameServer::notAllPlayersDisconnected(){
    return disconectedPlayers.size() < maxPlayers;
}

void GameServer::connectionLostWith(int id){

    disconectedPlayers.insert({ id, loggedPlayersID.at(id) });
    manager->disconectPlayerByID(id);
}

//CONTROLLER RELATED
//=========================================================================================

void GameServer::initController() {
    initSDL();
    controller = new Controller(this);
    lisentToInputForClosing = std::thread(&Controller::lisentToInputForClosing,controller);
    LogManager::logDebug("inicializado SDL");
    LogManager::logDebug("inicializado Controller");
}

void GameServer::closeController(){
    lisentToInputForClosing.join();
}

//LOGIN RELATED
//=========================================================================================
bool GameServer::serverFull(){
    return loggedPlayers.size() == maxPlayers;
}

bool GameServer::userInValidCredentials(string user){
    return validCredentials.find(user) != validCredentials.end();
}

bool GameServer::passInValidCredentials(string user,string pass){
    return validCredentials.at(user) == pass;
}

bool GameServer::userInLoggedPlayers(string user){
    return loggedPlayers.find(user) != loggedPlayers.end();
}

bool GameServer::IDInDisconnectedPlayers(int id){
    return disconectedPlayers.find(id) != disconectedPlayers.end();
}

string GameServer::processConectionAndEmitSuccesMessage(string user, string pass, int id){

    loggedPlayers.insert({ user, pass });
    loggedPlayersID.insert({ id, user });
    addNewIDToGame(id);

    return controller->getSuccesfullLoginMessage(id);
}

string GameServer::processReconectionAndEmitSuccesMessage(int id){

    disconectedPlayers.erase(id);
    manager->reconectPlayerByID(id);

    return controller->getSuccesfullLoginMessage(id);
}


//INIT
//=========================================================================================
void GameServer::initGameModel() {
    initECSManager();
    initLevelBuilder();
    LogManager::logDebug("inicializado Manager");
    LogManager::logDebug("inicializado LevelBuilder");
    LogManager::logInfo("Modelo inicializado");
}

void GameServer::init() {
    initConfig();
    loadValidCredenctials();
    maxPlayers = config->serverMaxPlayers;

    LogManager::logDebug("inicializado Config");
    LogManager::logDebug("cargado credenciales");
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
    this->levelBuilder = new LevelBuilder();
}

//DESTROY
//=========================================================================================

void GameServer::destroy() {
    delete(server);
    server = nullptr;
    delete(levelBuilder);
    levelBuilder = nullptr;
    delete(manager);
    manager = nullptr;
    baseClassFreeMemory();
    LogManager::logDebug("Memoria de Game Server liberada");
}