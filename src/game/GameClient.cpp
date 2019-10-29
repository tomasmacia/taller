#include <SDL2/SDL.h>

#include "../LogLib/Logger.h"
#include "GameClient.h"
#include "Controller.h"
#include "LoggerMenu.h"
#include "IDPlayer.h"



#include <iostream>

bool GameClient::hasInstance = false;

void GameClient::start() {

    isRunning = true;
    LogManager::logInfo("Se inicia GameClient");

    startLogin();
    initSDL();
    LogManager::logDebug("inicializado SDL");

    this->initController(); // instantiate out of constructor, since Controller uses Game::getInstance() and would create a deadlock
    LogManager::logDebug("inicializado Controller");

    while (isRunning) {
        pollAndSendInput();            //aca se podria cortar el game loop si se lee un ESC o QUIT
        render();
    }
    LogManager::logInfo("Juego terminado");
    LogManager::logInfo("=======================================");
}

void GameClient::pollAndSendInput() {
    controller->processInput();
    controller->sendInput();
}

void GameClient::render() {

    SDL_RenderClear(renderer);
    renderCadaPaquete();
    SDL_RenderPresent(renderer);

    std::cout<<"CLIENT: renderizo todo lo que me llego"<<'\n';
}

void GameClient::destroy() {

    delete(controller);
    controller = nullptr;
    delete(loginMenu);
    loginMenu = nullptr;
    //delete(socketManager);
    //socketManager = nullptr;
    clearTextureMap();
    SDL_DestroyWindow(this->window);
    SDL_DestroyRenderer(this->renderer);
    SDL_Quit();
    LogManager::logDebug("Memoria de Game liberada");
}

void GameClient::clearTextureMap(){

    for(std::map<std::string, TextureWrapper*>::iterator itr = loadedTexturesMap.begin(); itr != loadedTexturesMap.end(); itr++)
    {
        delete itr->second;
    }
}

void GameClient::init() {
    initConfig();
    //initiSocketManager();
    loginMenu = new LoggerMenu();

    LogManager::logDebug("inicializado Config");
    LogManager::logDebug("inicializado SocketManager");
    LogManager::logDebug("inicializado LoggerMenu");
    LogManager::logDebug("=======================================");
}

void GameClient::renderCadaPaquete(){
    for(auto package : packages){ package.render(loadedTexturesMap); }
}

void GameClient::startLogin(){

    //loginMenu->getValidCredentials(socketManager);
    LogManager::logInfo("Se inicia pantalla de login");
    if (!loginMenu->open()){
        end();
    }
    //loginMenu->sendUserPassLogged(socketManager);
    //this->playerId = socketManager->listen();
}
