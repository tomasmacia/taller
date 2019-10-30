#include <SDL2/SDL.h>

#include "../LogLib/Logger.h"
#include "GameClient.h"
#include "Controller.h"
#include "LoggerMenu.h"
#include <thread>



#include <iostream>

bool GameClient::hasInstance = false;

void GameClient::start() {
    LogManager::logInfo("Se inicia GameClient");

    //INIT CLIENT
    this->client = new Client(this);
    std::thread clientReadSend = std::thread(&Client::init, client);
    clientReadSend.join();
    LogManager::logInfo("inicializado Cliente");

    //LOGIN
    LoggerMenu* login = new LoggerMenu();
    LogManager::logInfo("Se inicia pantalla de login");
    if (login->open()){

        //INIT GAME
        this->initController(); // instantiate out of constructor, since Controller uses Game::getInstance() and would create a deadlock
        LogManager::logDebug("inicializado Controller");
        isRunning = true;

        //GAME LOOP
        while (isRunning) {
            pollAndSendInput();//aca se podria cortar el game loop si se lee un ESC o QUIT
            render();
        }
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
    this->initConfig();
    this->initSDL();

    LogManager::logDebug("inicializado Config");
    LogManager::logDebug("inicializado SDL");
    LogManager::logDebug("inicializado LoggerMenu");
    LogManager::logDebug("=======================================");
}

void GameClient::renderCadaPaquete(){
    for(auto package : packages){ package.render(loadedTexturesMap); }
}