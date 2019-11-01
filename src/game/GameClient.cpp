#include <SDL2/SDL.h>

#include "../LogLib/Logger.h"
#include <thread>
#include "Controller.h"
#include "LoggerMenu.h"
#include "GameClient.h"

#include <iostream>

bool GameClient::hasInstance = false;

void GameClient::start() {
    LogManager::logInfo("Se inicia GameClient");

    initClient();   //thread
    initLoggerMenu();

    if (loggerMenu->open()){

        initInputSystem();
        initRenderingSystem();

        gameLoop();
    }
    LogManager::logInfo("Juego terminado");
    LogManager::logInfo("=======================================");
}

//GAME LOOP
//=========================================================================================

void GameClient::gameLoop() {
    while (isRunning) {
        pollAndSendInput(); //aca se podria cortar el game loop si se lee un ESC o QUIT
        render();
    }
}

void GameClient::pollAndSendInput() {
    std::string serializedInput = controller->pollAndProcessInput();
    client->setToSend(serializedInput);
}

void GameClient::render() {

    SDL_RenderClear(renderer);
    renderAllPackages();
    SDL_RenderPresent(renderer);

    std::cout<<"CLIENT: renderizo todo lo que me llego"<<'\n';
}

void GameClient::renderAllPackages(){

    std::list<ToClientPack> packages = controller->getPackages();
    ToClientPack currentPackage;

    while (!packages.empty()){
        currentPackage = packages.front();
        packages.pop_front();
        currentPackage.render(&loadedTexturesMap);
    }
}

//API
//=========================================================================================
void GameClient::setPlayerId(int id) {
    playerId = id;
}

void GameClient::sendAknowledgeToLogerMenu(int id){
    //loggerMenu->sendServerResponse(id); TODO
}

void GameClient::reciveRenderable(ToClientPack package){
    controller->setRenderable(package);
}

//INIT
//=========================================================================================

void GameClient::initClient() {
    client = new Client(this);
    std::thread clientReadSend = std::thread(&Client::init, client);
    clientReadSend.join();
    LogManager::logInfo("inicializado Cliente");
}

void GameClient::initLoggerMenu(){
    loggerMenu = new LoggerMenu();
    LogManager::logDebug("inicializado LoggerMenu");
}

void GameClient::initInputSystem(){
    initController();
    LogManager::logDebug("inicializado Controller");
}

void GameClient::initRenderingSystem(){
    initSDL();
    LogManager::logDebug("inicializado SDL");
    isRunning = true;
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