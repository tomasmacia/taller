#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../LogLib/LogManager.h"
#include "Controller.h"
#include "../parser/CLIArgumentParser.h"
#include "../parser/xmlparser.h"
#include "../LogLib/Logger.h"
#include "LevelBuilder.h"
#include "GameServer.h"

#include <iostream>



void GameServer::init() {
    this->initConfig();
    this->initSDL();
    this->initECSManager();

    LogManager::logDebug("inicializado Config");
    LogManager::logDebug("inicializado SDL");
    LogManager::logDebug("inicializado ECSManager");
    LogManager::logDebug("=======================================");
}


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
    std::cout<<"MAGIA THREADS Y SOCKETS"<<'\n';
}

void GameServer::endLevel(){
    LogManager::logInfo("Nivel terminado");
    this->levelBuilder->endLevel();
}

void GameServer::end(){
    isRunning = false;
    LogManager::logDebug("señal de fin de juego emitida a Game");
}

int GameServer::getCurrentLevelWidth(){
    return levelBuilder->getCurrentLevelWidth();
}

void GameServer::initConfig() {
    string pathToConfigFile = CLIArgumentParser::getInstance().getPathToConfigFileName();

    XMLParser xmlParser;
    this->config = xmlParser.parse(pathToConfigFile);
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
    LogManager::logDebug("Memoria de Game liberada");
}

void GameServer::initSDL() {
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

void GameServer::initController() {
    this->controller = new Controller();
}

void GameServer::initECSManager() {
    this->manager = new Manager();
}