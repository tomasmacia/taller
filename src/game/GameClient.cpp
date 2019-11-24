#include <SDL2/SDL.h>

#include "../logger/Logger.h"
#include "Controller.h"
#include "../to_remove_or_modify/LoggerMenu.h"

bool GameClient::hasInstance = false;

void GameClient::start() {
    LogManager::logInfo("[GAME]: Se inicia GameClient");

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
        LogManager::logInfo("[GAME]: No se pudo conectar al servidor");
    }

    closeClient();

    LogManager::logInfo("[GAME]: Juego terminado");
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
    std::list<string> serializedInputs = controller->pollAndProcessInput();
    for (auto &input : serializedInputs) {
        client->setToSend(input);
    }
        //cout<<"CLIENT-FROM MODEL: "<<serializedInput<<endl;
}

void GameClient::render() {

    SDL_RenderClear(renderer);
    renderAllPackages();
    SDL_RenderPresent(renderer);
}

void GameClient::renderAllPackages(){
    if (controller != nullptr){
        controllerMutex.lock();
        std::list<Renderable*>* packages = controller->getPackages();

        if (packages->empty()){
            //cout<<endl;
            //cout << "CLIENT-RENDER: EMPTY!!!!" <<endl;
        }
        else{
            //cout<<endl;
            //cout << "CLIENT-RENDER: amount: " << packages->size() << endl;
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
    LogManager::logDebug("[GAME]: señal de fin de programa emitida");
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
    LogManager::logInfo("[INIT]: inicializado Cliente");
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
    LogManager::logDebug("[INIT]: inicializado LoggerMenu");
}

void GameClient::initInputSystem(){
    initController();
    LogManager::logDebug("[INIT]: inicializado Controller");
}

void GameClient::initRenderingSystem(){
    initSDL();
    LogManager::logDebug("[INIT]: inicializado SDL");
}

void GameClient::init() {
    initConfig();
    LogManager::logDebug("[INIT]: inicializado Config");
    LogManager::logDebug("=======================================");
}

void GameClient::initSDL() {
    if( SDL_Init(SDL_INIT_VIDEO) == 0 ) {
        if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
            LogManager::logError("Fallo SDL_Image");
        }

        int windowWidth = this->config->screenResolution.width;
        int windowHeight = this->config->screenResolution.height;

        string title = "FINAL FIGHT: Usuario: " + this->user + " Color: " + this->color;
        this->window = SDL_CreateWindow( title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, 0);
        this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_PRESENTVSYNC);
    }

    if (this->window == nullptr || this->renderer == nullptr) {
        this->on = false;
        LogManager::logError("SDL no pudo inicializarse");
    }
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

    for(auto & itr : loadedTexturesMap)
    {
        delete itr.second;
    }
}