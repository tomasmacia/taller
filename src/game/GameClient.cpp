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
    loggerMenu = new LoggerMenu();
    LogManager::logDebug("inicializado LoggerMenu");
    if (loggerMenu->open()){

        //INIT GAME
        initController(); // instantiate out of constructor, since Controller uses Game::getInstance() and would create a deadlock
        initSDL();
        LogManager::logDebug("inicializado SDL");
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
    std::string serializedInput = controller->processInput();
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
    ToClientPack currenPackage;

    while (!packages.empty()){
        currenPackage = packages.front();
        packages.pop_front();
        currenPackage.render(loadedTexturesMap);
    }
}

void GameClient::reconstructPackage(vector<string> splitedPackage){
    controller->reconstructPackage(splitedPackage);
}

void GameClient::setPlayerId(int id) {
    playerId = id;
}

void GameClient::sendAknowledgeToLogerMenu(int id){
    //loggerMenu->sendServerResponse(id); TODO
}

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

void GameClient::init() {
    this->initConfig();

    LogManager::logDebug("inicializado Config");
    LogManager::logDebug("=======================================");
}