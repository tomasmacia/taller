#include "../LogLib/LogManager.h"
#include "../parser/CLIArgumentParser.h"
#include "../parser/xmlparser.h"
#include "Game.h"
#include "Controller.h"

void Game::end(){
    isRunning = false;
    LogManager::logDebug("señal de fin de juego emitida a GameServer");
}

void Game::initConfig() {
    string pathToConfigFile = CLIArgumentParser::getInstance().getPathToConfigFileName();

    XMLParser xmlParser;
    this->config = xmlParser.parse(pathToConfigFile);
}

void Game::initController() {
    this->controller = new Controller(this);
}