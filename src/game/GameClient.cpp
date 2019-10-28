#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../LogLib/LogManager.h"
#include "Controller.h"
#include "../parser/CLIArgumentParser.h"
#include "../parser/xmlparser.h"
#include "../LogLib/Logger.h"
#include "GameClient.h"

void GameClient::start() {
    LogManager::logInfo("Se inicia GameClient");

    this->initController(); // instantiate out of constructor, since Controller uses Game::getInstance() and would create a deadlock
    LogManager::logDebug("inicializado Controller");

    isRunning = true;

    while (isRunning) {
        sendInput();
        render();
    }
    LogManager::logInfo("Juego terminado");
    LogManager::logInfo("=======================================");
}

void GameClient::init() {
    this->initConfig();
    this->initSDL();

    LogManager::logDebug("inicializado Config");
    LogManager::logDebug("=======================================");
}

void GameClient::initSDL() {
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
        this->isRunning = false;
        LogManager::logError("SDL no pudo inicializarse");
    } else {
        this->isRunning = true;
        //SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255);
    }
}

void GameClient::initController() {
    this->controller = new Controller();
}

void GameClient::initConfig() {
    string pathToConfigFile = CLIArgumentParser::getInstance().getPathToConfigFileName();

    XMLParser xmlParser;
    this->config = xmlParser.parse(pathToConfigFile);
}

void GameClient::destroy() {

    delete(controller);
    controller = nullptr;
    SDL_DestroyWindow(this->window);
    SDL_DestroyRenderer(this->renderer);
    SDL_Quit();
    LogManager::logDebug("Memoria de Game liberada");
}