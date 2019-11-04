#include "../LogLib/LogManager.h"
#include "Controller.h"
#include "../LogLib/Logger.h"
#include "LevelBuilder.h"
#include "GameServer.h"

#include "IDPlayer.h"

#include <iostream>

bool GameServer::hasInstance = false;

void GameServer::start() {
    LogManager::logInfo("Se inicia Game");

    initServer();
    waitUntilAllPlayersAreConected();

    initGameModel();
    gameLoop();

    LogManager::logInfo("Juego terminado");
    LogManager::logInfo("=======================================");
}

//GAME LOOP
//=========================================================================================

void GameServer::gameLoop(){

    isRunning = true;
    while (isRunning && levelBuilder->hasNextLevel()) {
        levelBuilder->loadNext();
        LogManager::logInfo("=======================================");
        LogManager::logInfo("se inicia game loop de este nivel");
        while (isRunning && !levelBuilder->levelFinished()) {
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

void GameServer::waitUntilAllPlayersAreConected(){
    while (server->numberOfConectionsEstablished() < amountOfConectionsNeeded){
        continue;
    }
}

std::string GameServer::validateLogin(std::string user, std::string pass, int userId){

    std::string serverFullMessage = controller->getServerFullMessage();
    std::string invalidCredentials = controller->getInvalidCredentialMessage();
    std::string alreadyLoggedInMessage = controller->getAlreadyLoggedInMessage();
    std::string succesfulLoginMessage = controller->getSuccesfullLoginMessage(userId);

    if (loggedPlayers.size() == amountOfConectionsNeeded){              //si esta lleno el server
        return serverFullMessage;
    }

    if ( validCredentials.find(user) == validCredentials.end() ) {      //si no es valido el user
        return invalidCredentials;
    }
    else {                                                              //si es valido el user
        if (validCredentials.at(user) == pass){                         //si es valido el pass
            if (loggedPlayers.find(user) == loggedPlayers.end()){       //si no esta ya logeado ese user/pass

                loggedPlayers.insert({ user, pass });
                addNewIDToGame(userId);

                return succesfulLoginMessage;
            }
            else{                                                        //si ya esta logeado ese user/pass
                return alreadyLoggedInMessage;
            }
        }
        else{
            return invalidCredentials;                                   //si es no es valido el pass
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

//INIT
//=========================================================================================

void GameServer::initServer(){
    server = new Server(this);
    server->init();
    LogManager::logInfo("Server inicializado");
}

void GameServer::initGameModel() {
    initECSManager();
    initController();
    initLevelBuilder();
    initSDL();
    LogManager::logDebug("inicializado Manager");
    LogManager::logDebug("inicializado Controller");
    LogManager::logDebug("inicializado LevelBuilder");
    LogManager::logInfo("Modelo inicializado");
}

void GameServer::init() {
    initConfig();
    loadValidCredenctials();
    //amountOfConectionsNeeded = config->gameplay.amountPlayers; TODO

    LogManager::logDebug("inicializado Config");
    LogManager::logDebug("cargado credenciales");
    LogManager::logDebug("=======================================");
}

void GameServer::loadValidCredenctials(){

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