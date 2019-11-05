#include <SDL2/SDL.h>

#include "../LogLib/Logger.h"
#include <thread>
#include "Controller.h"
#include "LoggerMenu.h"
#include "MessageId.h"

#include <iostream>

bool GameClient::hasInstance = false;

void GameClient::start() {
    LogManager::logInfo("Se inicia GameClient");

    startClient();          //1 thread de listen de conexiones nuevas y 3 threads para read, send y dispatch


    initLoggerMenu();

    if (loggerMenu->open()){

        initInputSystem();
        initRenderingSystem();

        gameLoop();
    }
/*
    initInputSystem();
    initRenderingSystem();

    gameLoop();
*/
    closeClient();

    LogManager::logInfo("Juego terminado");
    LogManager::logInfo("=======================================");
}

//GAME LOOP
//=========================================================================================

void GameClient::gameLoop() {
    while (isOn()) {
        pollAndSendInput(); //aca se podria cortar el game loop si se lee un ESC o QUIT
        render();
    }

}

void GameClient::pollAndSendInput() {
    std::string serializedInput = controller->pollAndProcessInput();
    if (serializedInput != ""){
        client->setToSend(serializedInput);
    }
}

void GameClient::render() {

    SDL_RenderClear(renderer);
    renderAllPackages();
    SDL_RenderPresent(renderer);
}

void GameClient::renderAllPackages(){
    std::list<ToClientPack*>* packages = controller->getPackages();
    ToClientPack* currentPackage;
    while (!packages->empty()){
        currentPackage = packages->front();
        packages->pop_front();
        currentPackage->render(&loadedTexturesMap);
    }
}

//API
//=========================================================================================
void GameClient::setPlayerId(int id) {
    playerId = id;
}

void GameClient::setServerAknowledgeToLogin(MessageId id){
    //loggerMenu->setServerAknowledge(id); TODO
}

void GameClient::reciveRenderable(ToClientPack* package){
    controller->setRenderable(package);
}


//CLIENT RELATED
//=========================================================================================
void GameClient::startClient() {
    client = new Client(this);
    clientConnectionThread = std::thread(&Client::start,client);
    LogManager::logInfo("inicializado Cliente");
}

void GameClient::closeClient() {
    clientConnectionThread.join();
}

//INIT
//=========================================================================================

void GameClient::initLoggerMenu(){
    loggerMenu = new LoggerMenu(client);
    LogManager::logDebug("inicializado LoggerMenu");
}

void GameClient::initInputSystem(){
    initController();
    LogManager::logDebug("inicializado Controller");
}

void GameClient::initRenderingSystem(){
    initSDL();
    LogManager::logDebug("inicializado SDL");
}

void GameClient::init() {
    initConfig();

    LogManager::logDebug("inicializado Config");
    LogManager::logDebug("=======================================");
}

//DESTROY
//=========================================================================================

void GameClient::destroy() {
    delete(loggerMenu);
    loggerMenu = nullptr;
    delete(client);
    client = nullptr;
    clearTextureMap();
    baseClassFreeMemory();
    LogManager::logDebug("Memoria de Game Client liberada");
}

void GameClient::clearTextureMap(){

    for(std::map<std::string, TextureWrapper*>::iterator itr = loadedTexturesMap.begin(); itr != loadedTexturesMap.end(); itr++)
    {
        delete itr->second;
    }
}