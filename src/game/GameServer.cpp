#include "../LogLib/LogManager.h"
#include "Controller.h"
#include "../LogLib/Logger.h"
#include "LevelBuilder.h"
#include "GameServer.h"

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


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
            render();
            //sendUpdate();
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

void GameServer::render() { // TODO SOLO PARA PROBARLO HASTA TENER LOS SOCKETS (BORRAR)
    SDL_RenderClear(renderer);
    manager->render();
    SDL_RenderPresent(renderer);
}

void GameServer::sendUpdate() {
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
    LogManager::logDebug("Memoria de GameServer liberada");
}

void GameServer::init() {
    this->initConfig();
    this->initECSManager();




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






    LogManager::logDebug("inicializado Config");
    LogManager::logDebug("inicializado ECSManager");
    LogManager::logDebug("=======================================");
}

void GameServer::initECSManager() {
    this->manager = new Manager();
}