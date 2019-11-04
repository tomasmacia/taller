#include "../LogLib/LogManager.h"
#include "Controller.h"
#include "../LogLib/Logger.h"
#include "LevelBuilder.h"
#include "GameServer.h"

#include "IDPlayer.h"

#include <iostream>

bool GameServer::hasInstance = false;

void GameServer::start() {
    LogManager::logInfo("Se inicia Game");

    initController();       //1 thread para escuchar teclado y la crucecita de la window
    startServer();          //1 thread de listen de conexiones nuevas y 4 threads por cliente nuevo

    initGameModel();
    gameLoop();

    cout<<"tlalaa!"<<endl;
    listenConnectionsThread.join();
    lisentToInputForClosing.join();
    cout<<"olololololo!"<<endl;

    LogManager::logInfo("Juego terminado");
    LogManager::logInfo("=======================================");

    cout<<"everything endded up nicely :D"<<endl;
}

//GAME LOOP
//=========================================================================================

void GameServer::gameLoop(){

    while (isOn() && levelBuilder->hasNextLevel()) {
        levelBuilder->loadNext();
        LogManager::logInfo("=======================================");
        LogManager::logInfo("se inicia game loop de este nivel");
        while (isOn() && !levelBuilder->levelFinished()) {
            update();
            sendUpdate();
        }
        LogManager::logInfo("fin de game loop de este nivel");
        LogManager::logInfo("=======================================");
    }
}

void GameServer::update() {
    manager->update();
    controller->clearAllInputs();
}

void GameServer::sendUpdate() {
    controller->sendUpdate(manager->generateRenderables(),server);
}

//API
//=========================================================================================

std::string GameServer::validateLogin(std::string user, std::string pass, int userId){

    std::string serverFullMessage = controller->getServerFullMessage();
    std::string invalidCredentials = controller->getInvalidCredentialMessage();
    std::string alreadyLoggedInMessage = controller->getAlreadyLoggedInMessage();
    std::string succesfulLoginMessage = controller->getSuccesfullLoginMessage(userId);

    if (loggedPlayers.size() == amountOfConectionsNeeded){              //si esta lleno el server
        return serverFullMessage;
    }

    if ( validCredentials.find(user) == validCredentials.end() ) {      //si no es valido el user
        return invalidCredentials;
    }
    else {                                                              //si es valido el user
        if (validCredentials.at(user) == pass){                         //si es valido el pass
            if (loggedPlayers.find(user) == loggedPlayers.end()){       //si no esta ya logeado ese user/pass

                loggedPlayers.insert({ user, pass });
                addNewIDToGame(userId);

                return succesfulLoginMessage;
            }
            else{                                                        //si ya esta logeado ese user/pass
                return alreadyLoggedInMessage;
            }
        }
        else{
            return invalidCredentials;                                   //si es no es valido el pass
        }
    }
}

void GameServer::endLevel(){
    LogManager::logInfo("Nivel terminado");
    levelBuilder->endLevel();
}

void GameServer::addNewIDToGame(int id) {
    IDPlayer::getInstance().addNewIdPlayer(id);
}

int GameServer::getCurrentLevelWidth(){
    return levelBuilder->getCurrentLevelWidth();
}

void GameServer::reciveNewInput(tuple<Action,int> input){
    return controller->setInput(input);
}

bool GameServer::isActive(){
    return hasInstance;
}

//SERVER RELATED
//=========================================================================================
void GameServer::startServer(){
    server = new Server(this);
    server->init();
    listenConnectionsThread = std::thread(&Server::listenThread,server);
    LogManager::logInfo("Server inicializado");
}


//CONTROLLER RELATED
//=========================================================================================

void GameServer::initController() {
    initSDL();
    controller = new Controller(this);
    lisentToInputForClosing = std::thread(&Controller::lisentToInputForClosing,controller);
    LogManager::logDebug("inicializado SDL");
    LogManager::logDebug("inicializado Controller");
}

//INIT
//=========================================================================================
void GameServer::initGameModel() {
    initECSManager();
    initLevelBuilder();
    LogManager::logDebug("inicializado Manager");
    LogManager::logDebug("inicializado LevelBuilder");
    LogManager::logInfo("Modelo inicializado");
}

void GameServer::init() {
    initConfig();
    loadValidCredenctials();
    //amountOfConectionsNeeded = config->gameplay.amountPlayers; TODO

    LogManager::logDebug("inicializado Config");
    LogManager::logDebug("cargado credenciales");
    LogManager::logDebug("=======================================");
}

void GameServer::loadValidCredenctials(){

}

void GameServer::initECSManager() {
    this->manager = new Manager();
}

void GameServer::initLevelBuilder() {
    this->levelBuilder = new LevelBuilder();
}

//DESTROY
//=========================================================================================

void GameServer::destroy() {
    delete(server);
    server = nullptr;
    delete(levelBuilder);
    levelBuilder = nullptr;
    delete(manager);
    manager = nullptr;
    baseClassFreeMemory();
    LogManager::logDebug("Memoria de Game Server liberada");
}