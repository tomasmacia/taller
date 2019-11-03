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

    initClient();
    /*
    initLoggerMenu();

    if (loggerMenu->open()){

        initInputSystem();
        initRenderingSystem();

        gameLoop();
    }*/
    initInputSystem();
    initRenderingSystem();

    gameLoop();

    LogManager::logInfo("Juego terminado");
    LogManager::logInfo("=======================================");
}

//GAME LOOP
//=========================================================================================

void GameClient::gameLoop() {
    isRunning = true;
    while (isRunning) {
        pollAndSendInput(); //aca se podria cortar el game loop si se lee un ESC o QUIT
        render();
    }
}

void GameClient::pollAndSendInput() {
    /*if(controller->hasNewInput()){
        std::string serializedInput = controller->pollAndProcessInput();
        cout<<"CLIENT-INPUT: "<<serializedInput<<endl;
        client->setToSend(serializedInput);
    }*/
    std::string serializedInput = controller->pollAndProcessInput();

    if (serializedInput != ""){
        cout<<"CLIENT-INPUT: "<<serializedInput<<endl;
        client->setToSend(serializedInput);
    }
}

void GameClient::render() {

    SDL_RenderClear(renderer);
    renderAllPackages();
    SDL_RenderPresent(renderer);

    //cout<<"CLIENT: renderizo todo lo que me llego"<<endl;
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

void GameClient::setServerAknowledgeToLogin(MessageId id){
    //loggerMenu->setServerAknowledge(id); TODO
}

void GameClient::reciveRenderable(ToClientPack package){
    controller->setRenderable(package);
}

//INIT
//=========================================================================================

void GameClient::initClient() {
    client = new Client(this);
    client->init();
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