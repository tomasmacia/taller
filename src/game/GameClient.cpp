#include <SDL2/SDL.h>

#include "../LogLib/Logger.h"
#include "Controller.h"
#include "LoggerMenu.h"
#include "MessageId.h"

#include <iostream>

bool GameClient::hasInstance = false;

void GameClient::start() {
    LogManager::logInfo("Se inicia GameClient");

    startClient();               //1 thread de listen de conexiones nuevas y 3 threads para read, send y dispatch
    initLoggerMenu();

    waitUntilConnectionStablished();

    if (isOn()){                //pregunto porque el Client lo podria haber cerrado al no conectarse
        loggerMenu->open();

        if (isOn()){            //pregunto porque el loggerMenu lo podria haber cerrado al tocar ESC o QUIT
            initInputSystem();
            initRenderingSystem();

            gameLoop();
        }
    }
    else{
        LogManager::logInfo("No se pudo conectar al servidor");
    }

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
        cout<<"CLIENT-FROM MODEL: "<<serializedInput<<endl;
    }
}

void GameClient::render() {

    SDL_RenderClear(renderer);
    renderAllPackages();
    SDL_RenderPresent(renderer);
}

void GameClient::renderAllPackages(){
    if (controller != nullptr){
        controllerMutex.lock();
        std::list<ToClientPack*>* packages = controller->getPackages();

        if (packages->empty()){
            cout<<endl;
            cout << "CLIENT-RENDER: EMPTY!!!!" <<endl;
        }
        else{
            cout<<endl;
            cout << "CLIENT-RENDER: amount: " << packages->size() << endl;
            for (auto package : *packages) {
                package->render(&loadedTexturesMap);
                //cout << "CLIENT-RENDER: " << package->getPath() << endl;
            }
        }
        controllerMutex.unlock();
    }
}

//API
//=========================================================================================
void GameClient::setPlayerId(int id) {
    playerId = id;
}

void GameClient::setServerAknowledgeToLogin(MessageId id){
    loggerMenu->serverAcknowledge(id);
}

void GameClient::notifyAboutClientConectionToServerAttemptDone(){
    waitForConnection.notify_one();
}

void GameClient::end() {
    on = false;
    client->notifyGameStoppedRunning();
    LogManager::logDebug("señal de fin de programa emitida");
}

bool GameClient::alreadyLoggedIn() {
    return loggedIn;
}

void GameClient::reciveRenderables(vector<string>* serializedPages){
    if (controller != nullptr){
        controllerMutex.lock();
        controller->reciveRenderables(serializedPages);
        controllerMutex.unlock();
    }
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

bool GameClient::hasClientAttemptedConection(){
    return client->hasAchievedConnectionAttempt();
}

void GameClient::waitUntilConnectionStablished(){
    //para que no llegue antes el main que el intento de conexion de client
    std::unique_lock<std::mutex> lck (mu);
    waitForConnection.wait(lck, [this]{ return hasClientAttemptedConection();});
}

//INIT
//=========================================================================================

void GameClient::initLoggerMenu(){
    loggerMenu = new LoggerMenu(client,this);
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