#include "GameServer.h"
#include "Controller.h"
#include "LevelBuilder.h"
#include "../LogLib/Logger.h"
#include "../LogLib/LogManager.h"
#include "../parser/CLIArgumentParser.h"
#include "../parser/xmlparser.h"
#include <unistd.h>

#include "IDPlayer.h"

#include <iostream>

bool GameServer::hasInstance = false;

void GameServer::start() {
    LogManager::logInfo("Se inicia Game");

    initController();
    startServer();          //1 thread de listen de conexiones nuevas y 4 threads por cliente nuevo

    waitUnitAllPlayersConnected();

    initGameModel();
    gameLoop();

    closeServer();          //se cierra el thread se server y (previamente se cierran los 4 threads child)

    LogManager::logInfo("Juego terminado");
    LogManager::logInfo("=======================================");

    cout << "everything endded up nicely :D" << endl;
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
            usleep(13000);
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

    if (serverFull() && !userInLoggedPlayers(user)){
        return controller->getServerFullMessage();
    }
    else{
        if (userInValidCredentials(user)){
            if (passInValidCredentials(user,pass)){
                if(userInLoggedPlayers(user)){
                    if(IDInDisconnectedPlayers(user)){
                        return processReconectionAndEmitSuccesMessage(user,userId);
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
    return loggedPlayersPassByUser.size() == maxPlayers;
}

bool GameServer::isIDLogged(int ID){
    return loggedPlayersUserByID.count( ID );
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
    listenConnectionsThread.join();
}

void GameServer::waitUnitAllPlayersConnected(){

    while ((loggedPlayersPassByUser.size() != maxPlayers) ||
            (disconectedPlayers.size() != 0)){

        continue;
    }
}

bool GameServer::notAllPlayersDisconnected(){
    return disconectedPlayers.size() < maxPlayers;
}

void GameServer::connectionLostWith(int id){

    if (loggedPlayersUserByID.count(id)){

        string user = loggedPlayersUserByID.at(id);
        disconectedPlayers.insert({user,id});
    }
    if (manager != nullptr){
        manager->disconectPlayerByID(id);
    }
}

//CONTROLLER RELATED
//=========================================================================================

void GameServer::initController() {
    controller = new Controller(this);
    LogManager::logDebug("inicializado Controller");
}

void GameServer::closeController(){
    //lisentToInputForClosing.join();
}

//LOGIN RELATED
//=========================================================================================
bool GameServer::serverFull(){
    return loggedPlayersPassByUser.size() == maxPlayers;
}

bool GameServer::userInValidCredentials(string user){
    return validCredentials.find(user) != validCredentials.end();
}

bool GameServer::passInValidCredentials(string user,string pass){
    return validCredentials.at(user) == pass;
}

bool GameServer::userInLoggedPlayers(string user){
    return loggedPlayersPassByUser.find(user) != loggedPlayersPassByUser.end();
}

bool GameServer::IDInDisconnectedPlayers(string user){
    return disconectedPlayers.find(user) != disconectedPlayers.end();
}

string GameServer::processConectionAndEmitSuccesMessage(string user, string pass, int id){

    loggedPlayersPassByUser.insert({ user, pass });
    loggedPlayersUserByID.insert({ id, user });
    loggedPlayersIDbyUser.insert({user,id});
    addNewIDToGame(id);

    return controller->getSuccesfullLoginMessage(id);
}

string GameServer::processReconectionAndEmitSuccesMessage(string user, int newID){

    int oldID = loggedPlayersIDbyUser.at(user);
    loggedPlayersUserByID.erase(oldID);
    loggedPlayersUserByID.insert({newID,user});

    loggedPlayersIDbyUser.at(user) = newID;

    disconectedPlayers.erase(user);
    if (manager != nullptr){
        manager->reconectPlayerByID(oldID, newID);
    }

    return controller->getSuccesfullLoginMessage(newID);
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