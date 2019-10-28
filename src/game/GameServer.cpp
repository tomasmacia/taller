#include "../LogLib/LogManager.h"
#include "GameServer.h"

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



void GameServer::init() {
    this->initConfig();
    this->initSDL();
    this->initECSManager();

    LogManager::logDebug("inicializado Config");
    LogManager::logDebug("inicializado SDL");
    LogManager::logDebug("inicializado ECSManager");
    LogManager::logDebug("=======================================");
}