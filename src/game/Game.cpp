#include "Game.h"
#include "../LogLib/LogManager.h"
#include <SDL2/SDL.h>
#include <SDL_image.h>

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

void Game::initSDL() {
    if( SDL_Init(SDL_INIT_VIDEO) == 0 ) {
        if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
            LogManager::logError("Fallo SDL_Image");
        }

        int windowWidth = this->config->screenResolution.width;
        int windowHeight = this->config->screenResolution.height;

        this->window = SDL_CreateWindow("Final Fight", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, 0);
        this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_PRESENTVSYNC);
    }

    if (this->window == nullptr || this->renderer == nullptr) {
        this->on = false;
        LogManager::logError("SDL no pudo inicializarse");
    }
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