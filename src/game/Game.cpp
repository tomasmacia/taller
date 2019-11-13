#include "Game.h"
#include "../LogLib/LogManager.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <algorithm>
#include "../parser/CLIArgumentParser.h"
#include "../parser/xmlparser.h"
#include "Controller.h"

//API
//=========================================================================================

void Game::end(){
    on = false;
    LogManager::logDebug("señal de fin de programa emitida");
}

bool Game::isOn(){
    return on;
}

//INIT
//=========================================================================================

void Game::initConfig() {
    string pathToConfigFile = CLIArgumentParser::getInstance().getPathToConfigFileName();

    XMLParser xmlParser;
    this->config = xmlParser.parse(pathToConfigFile);
}

void Game::initController() {
    controller = new Controller(this);
}

//DESTROY
//=========================================================================================

void Game::baseClassFreeMemory(){
    delete(controller);
    controller = nullptr;
    delete(config);
    config = nullptr;
    SDL_DestroyWindow(this->window);
    SDL_DestroyRenderer(this->renderer);
    SDL_Quit();
}