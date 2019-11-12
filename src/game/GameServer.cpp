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
    LogManager::logInfo("[GAME]: Se inicia Game");

    initController();
    startServer();          //1 thread de listen de conexiones nuevas y 4 threads por cliente nuevo

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
            usleep(13000);
        }
        LogManager::logInfo("[GAME]: fin de game loop de este nivel");
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
    controller->sendUpdate(manager->generateRenderables(),server);
}

//API
//=========================================================================================

std::string GameServer::validateLogin(std::string user, std::string pass, int userId){


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

void GameServer::endLevel(){
    LogManager::logInfo("[GAME]: Nivel terminado");
    levelBuilder->endLevel();
}

void GameServer::addNewIDToGame(int id) {
    IDPlayer::getInstance().addNewIdPlayer(id);
}

void GameServer::reemplazePreviousIDWith(int oldID, int newID) {
    IDPlayer::getInstance().reemplaze(oldID, newID);
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
    LogManager::logInfo("[INIT]: Server inicializado");
}

void GameServer::closeServer(){
    listenConnectionsThread.join();
    server->close();
}

void GameServer::waitUnitAllPlayersConnected(){

    while ((loggedPlayersPassByUser.size() != maxPlayers) ||
            (!disconectedPlayers.empty())){}
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
    LogManager::logDebug("[INIT]: inicializado Controller");
}

void GameServer::closeController(){
    //lisentToInputForClosing.join();
}

//LOGIN RELATED
//=========================================================================================
bool GameServer::serverFull(){
    return loggedPlayersPassByUser.size() == maxPlayers;
}

bool GameServer::credentialsAreValid(string user, string pass){
    return validUser(user) && validPass(user,pass);
}

bool GameServer::userAlreadyLoggedIn(string user){
    return userInLoggedPlayers(user);
}

bool GameServer::userIsDisconnected(string user){
    return IDInDisconnectedPlayers(user);
}

bool GameServer::validUser(string user){
    return validCredentials.find(user) != validCredentials.end();
}

bool GameServer::validPass(string user, string pass){
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

    reemplazePreviousIDWith(oldID, newID);

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