#include <SDL2/SDL.h>

#include "../logger/Logger.h"
#include "Controller.h"
#include "LoggerMenu.h"
#include "GameClient.h"


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
            initSceneDirector();
            initRenderingSystem();
            initSoundSystem();
            client->client_noBlock(); //que el send y recv al cliente no bloqueen el juego

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
    initGameMusic();
    sceneDirector->initDisconectionScreen();
    sceneDirector->initVictoryScreen();
    sceneDirector->initLossingScreen();
    while (isOn()) {
        pollAndSendInput(); //aca se podria cortar el game loop si se lee un ESC o QUIT
        updateMusic();
        updateRendering();
    }
}

void GameClient::pollAndSendInput() {
    std::list<string> serializedInputs = controller->pollAndProcessInput();
    for (auto &input : serializedInputs) {
        client->setToSend(input);
    }
        //cout<<"CLIENT-FROM MODEL: "<<serializedInput<<endl;
}

void GameClient::updateMusic() {
    if ((disconnect || playerDied) && !endOfGame){
        if (!youDiedMusicPlaying){

            initYouDiedOrDisconnectedMusic();
            gameMusic->play(1);
            youDiedMusicPlaying = true;
            normalGameMusicPlaying = false;
        }
    }

    else if(gameWon){
        if (!gameWonMusicPlaying){
            initVictoryMusic();
            gameMusic->play(1);
            youDiedMusicPlaying = false;
            normalGameMusicPlaying = false;
            gameWonMusicPlaying = true;
            gameLostMusicPlaying = false;
        }
    }

    else if(gameLost){
        if (!gameLostMusicPlaying){
            initLossingMusic();
            gameMusic->play(1);
            youDiedMusicPlaying = false;
            normalGameMusicPlaying = false;
            gameWonMusicPlaying = false;
            gameLostMusicPlaying = true;
        }
    }

    else if (gameStarted){
        if (!normalGameMusicPlaying){

            gameMusic->play();
            normalGameMusicPlaying = true;
            youDiedMusicPlaying = false;
        }
    }
}

void GameClient::updateRendering() {
    if (disconnect && !endOfGame){
        sceneDirector->renderDisconectionScreen(renderer, &loadedTexturesMap);
    }
    else if (gameWon){
        for (int i = 0; i < END_SCREEN_FRAMES; i++){
            sceneDirector->renderVictoryScreen(renderer, &loadedTexturesMap);
        }
        end();
    }
    else if (gameLost) {
        for (int i = 0; i < END_SCREEN_FRAMES; i++) {
            sceneDirector->renderLossingScreen(renderer, &loadedTexturesMap);
        }
        end();
    }
    else {
        render();
    }
}

void GameClient::render() {

    SDL_RenderClear(renderer);
    renderAllPackages();
    SDL_RenderPresent(renderer);
}

void GameClient::renderAllPackages(){
    //cout<<"GAME LOOP"<<endl;
    if (controller != nullptr){
        controllerMutex.lock();

        if (controller->hasNewPackages()){
            if (!previousPackages->empty()){
                int x = 0;
            }
            erasePreviousPackages();
            previousPackages->splice(previousPackages->end(),*controller->getPackages()); //se transfieren los punteros trackeados en Controller vaciando la lista de Controller
        }

        int i  = 0;
        for (auto package : *previousPackages) { // si ya se, es raro que si vinieron paquetes nuevos usemos el previousPackages pero eso que estos ahora estan actualizados

            if (package->hasRenderable()){
                package->_renderable->render(&loadedTexturesMap);
            }
            if (package->hasSoundable()){
                //cout<<"ejecuto sonido: "<<package->_soundable->getPath()<<" ,cant total paquetes a ejecutar: "<<previousPackages->size()<<" | i = "<<i<<endl;
                package->_soundable->play(&loadedSoundsMap);
            }
            i++;
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
    Game::end();
    client->notifyGameStoppedRunning();
}

void GameClient::reciveRenderables(vector<string>* serializedPages){

    if (controller != nullptr){
        controllerMutex.lock();
        controller->reciveRenderables(serializedPages);
        controllerMutex.unlock();
    }
}

void GameClient::notifyEndOfGame() {
    endOfGame = true;
    gameWon = endOfGame && !playerDied;
    gameLost = !gameWon;
    LogManager::logInfo("[GAME]: Señal de fin de juego recibida desde el server");
}

void GameClient::processPlayerDeath(int id) {
    if (id == playerId){
        playerDied = true;
        LogManager::logInfo("[GAME]: Señal de jugador muerto recibida desde el server");
    }
}

void GameClient::notifyGameStart() {
    gameStarted = true;
    LogManager::logInfo("[GAME]: Señal de principio de juego recibida desde el server");
}

bool GameClient::hasDeadPlayer(){
    return playerDied;
}

//SOUND
//=========================================================================================

void GameClient::initGameMusic() {
    gameMusic = new SoundWrapper(true);
    gameMusic->load(GAME_MUSIC_PATH);
}

void GameClient::initYouDiedOrDisconnectedMusic() {
    gameMusic->load(YOU_DIED_OR_DISCONNECTED_MUSIC_PATH);
}

void GameClient::initVictoryMusic() {
    gameMusic->load(VICTORY_MUSIC_PATH);
}

void GameClient::initLossingMusic() {
    gameMusic->load(LOSSING_MUSIC_PATH);
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

void GameClient::initSoundSystem(){
    initSDLMixer();
    LogManager::logDebug("[INIT]: inicializado SDL Mixer");
}

void GameClient::init() {
    previousPackages = new list<Sendable*>();
    initConfig();
    LogManager::logDebug("[INIT]: inicializado Config");
    LogManager::logDebug("=======================================");
}

void GameClient::disconnected(){
    disconnect = true;
    LogManager::logInfo("[GAME]: Señal de desconexion recibida de Client");
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
        end();
        LogManager::logError("SDL no pudo inicializarse");
    }
}

void GameClient::initSDLMixer() {

    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        LogManager::logError("SDL MIXER no pudo inicializarse el");
    }

    if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
    {
        LogManager::logError("SDL MIXER no pudo inicializarse");
    }
}

//DESTROY
//=========================================================================================

void GameClient::destroy() {
    erasePreviousPackages();
    delete(previousPackages);
    previousPackages = nullptr;
    delete(loggerMenu);
    loggerMenu = nullptr;
    delete(client);
    client = nullptr;
    delete (gameMusic);
    clearMaps();
    baseClassFreeMemory();
    LogManager::logDebug("[GAME]: Memoria de Game Client liberada");
}

void GameClient::clearMaps(){

    for(auto & itr : loadedTexturesMap)
    {
        delete itr.second;
    }

    for(auto & itr : loadedSoundsMap)
    {
        delete itr.second;
    }
}

void GameClient::erasePreviousPackages() {
    int x = 0;
    for (Sendable* package : *previousPackages){
        delete package;
        x++;
    }
    previousPackages->clear();
}

void GameClient::directSendToServer(string message) {
    client->setToSend(message);
}

void GameClient::connected() {
    disconnect = false;
    LogManager::logInfo("[GAME]: Señal de conexion recibida desde el Client");
}

