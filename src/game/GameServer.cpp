#include "../LogLib/LogManager.h"
#include "Controller.h"
#include "../LogLib/Logger.h"
#include "LevelBuilder.h"
#include "GameServer.h"

#include <iostream>


bool GameServer::hasInstance = false;

void GameServer::start() {
    LogManager::logInfo("Se inicia Game");

    this->initController(); // instantiate out of constructor, since Controller uses Game::getInstance() and would create a deadlock
    levelBuilder = new LevelBuilder();
    LogManager::logDebug("inicializado LevelBuilder");
    LogManager::logDebug("inicializado Controller");

    isRunning = true;

    while (isRunning && levelBuilder->hasNextLevel()) {
        levelBuilder->loadNext();

        LogManager::logInfo("=======================================");
        LogManager::logInfo("se inicia game loop de este nivel");
        while (isRunning && !levelBuilder->levelFinished()) {
            processInput();
            update();
            sendUpdate();
        }
        LogManager::logInfo("fin de game loop de este nivel");
        LogManager::logInfo("=======================================");
    }
    LogManager::logInfo("Juego terminado");
    LogManager::logInfo("=======================================");
}

void GameServer::processInput() {
    controller->processInput();
}

void GameServer::update() {
    manager->update();
}

void GameServer::sendUpdate() {
    toClientsPackages = manager->generateRenderables();
    //socketManager->broadcast(toClientsPackages);  TODO
    std::cout<<"SERVER: mando paquetes a clientes"<<'\n';
}

void GameServer::endLevel(){
    LogManager::logInfo("Nivel terminado");
    this->levelBuilder->endLevel();
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

    LogManager::logDebug("inicializado Config");
    LogManager::logDebug("inicializado ECSManager");
    LogManager::logDebug("inicializado SDL");
    LogManager::logDebug("=======================================");
}

void GameServer::initECSManager() {
    this->manager = new Manager();
}