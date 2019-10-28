#include "../LogLib/LogManager.h"
#include "GameClient.h"

void GameClient::start() {
    LogManager::logInfo("Se inicia GameClient");

    this->initController(); // instantiate out of constructor, since Controller uses Game::getInstance() and would create a deadlock
    LogManager::logDebug("inicializado Controller");

    isRunning = true;

    while (isRunning && !levelFinished) {
        sendInput();
        render();
    }
    LogManager::logInfo("Juego terminado");
    LogManager::logInfo("=======================================");
}