#include "../LogLib/LogManager.h"
#include "Controller.h"
#include "../LogLib/Logger.h"
#include "LevelBuilder.h"
#include "GameServer.h"
#include <thread>
#include "IDPlayer.h"

#include <iostream>

bool GameServer::hasInstance = false;

void GameServer::start() {
    LogManager::logInfo("Se inicia Game");

    initServer();   //thread
    //waitUntilAllPlayersAreConected();

    initGameModel();
    gameLoop();

    LogManager::logInfo("Juego terminado");
    LogManager::logInfo("=======================================");
}

//GAME LOOP
//=========================================================================================

void GameServer::gameLoop(){

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
}

void GameServer::sendUpdate() {
    toClientsPackages = manager->generateRenderables();
    controller->sendUpdate(toClientsPackages,server);
    std::cout<<"SERVER: mando paquetes a clientes"<<'\n';
}

//API
//=========================================================================================

void GameServer::waitUntilAllPlayersAreConected(){
    while (server->numberOfConectionsEstablished() <= amountOfConectionsNeeded){
        continue;
    }
}

std::string GameServer::validateLogin(std::string user, std::string pass, int userId){

    std::string failedLoginMessage = controller->getFailedLoginMessage();
    std::string succesfulLoginMessage = controller->getSuccesfullLoginMessage(userId);

    if ( validCredentials.find(user) == validCredentials.end() ) {
        return failedLoginMessage;
    }
    else {
        if (validCredentials.at(user) == pass){
            if (loggedPlayers.find(user) == loggedPlayers.end()){
                loggedPlayers.insert({ user, pass });
                addNewIDToGame(userId);
                return succesfulLoginMessage;
            }
            else{
                return failedLoginMessage;
            }
        }
        else{
            return failedLoginMessage;
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
    std::thread listen = std::thread(&Server::listenThread, server);
    listen.join();
    LogManager::logInfo("Server inicializado");
}

void GameServer::initGameModel() {
    initGameModel();
    initECSManager();
    initController();
    initLevelBuilder();
    isRunning = true;
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