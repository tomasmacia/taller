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

    //INIT SERVER
    this->server = new Server(this);
    server->init();
    std::thread listen = std::thread(&Server::listenThread, server);
    listen.join();
    LogManager::logInfo("inicializado Server");
    waitUntilAllPlayersAreConected();

    //INIT GAME
    this->initController(); // instantiate out of constructor, since Controller uses Game::getInstance() and would create a deadlock
    levelBuilder = new LevelBuilder();
    LogManager::logDebug("inicializado LevelBuilder");
    LogManager::logDebug("inicializado Controller");
    isRunning = true;

    //GAME LOOP
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
    LogManager::logInfo("Juego terminado");
    LogManager::logInfo("=======================================");
}

void GameServer::update() {
    manager->update();
}

void GameServer::sendUpdate() {
    toClientsPackages = manager->generateRenderables();
    controller->sendUpdate(toClientsPackages,server);
    std::cout<<"SERVER: mando paquetes a clientes"<<'\n';
}

void GameServer::endLevel(){
    LogManager::logInfo("Nivel terminado");
    this->levelBuilder->endLevel();
}

std::string GameServer::validateLogin(std::string user, std::string pass, int userId){

    std::string failedLoginMessage = "0_-1_x" ;
    std::string succesLoginMessage = "0_" + std::to_string(userId) + "_x";

    if ( validCredentials.find(user) == validCredentials.end() ) {
        return failedLoginMessage;
    }
    else {
        if (validCredentials.at(user) == pass){
            if (loggedPlayers.find(user) == loggedPlayers.end()){
                loggedPlayers.insert({ user, pass });
                return succesLoginMessage;
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

void GameServer::waitUntilAllPlayersAreConected(){
    while (server->numberOfConectionsEstablished() <= amountOfConectionsNeeded){
        continue;
    }
}

void GameServer::addNewIDToGame(int id) {
    IDPlayer::getInstance().addNewIdPlayer(id);
}

void GameServer::reconstructInput(std::string action, std::string id){
    controller->reconstructInput(action,id);
}


int GameServer::getCurrentLevelWidth(){
    return levelBuilder->getCurrentLevelWidth();
}

void GameServer::destroy() {

    delete(levelBuilder);
    levelBuilder = nullptr;
    delete(controller);
    controller = nullptr;
    delete(manager);
    manager = nullptr;
    SDL_DestroyWindow(this->window);
    SDL_DestroyRenderer(this->renderer);
    SDL_Quit();
    LogManager::logDebug("Memoria de GameServer liberada");
}

void GameServer::init() {
    this->initConfig();
    this->initECSManager();
    this->initSDL();
    loadValidCredenctials();
    //amountOfConectionsNeeded = config->gameplay.amountPlayers; TODO

    LogManager::logDebug("cargado credenciales");
    LogManager::logDebug("inicializado Config");
    LogManager::logDebug("inicializado ECSManager");
    LogManager::logDebug("inicializado SDL");
    LogManager::logDebug("=======================================");
}

void GameServer::loadValidCredenctials(){

}

void GameServer::initECSManager() {
    this->manager = new Manager();
}