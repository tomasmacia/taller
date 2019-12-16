#include "Game.h"
#include "../logger/LogManager.h"
#include <SDL2/SDL.h>

#include <iostream>
#include <algorithm>
#include "../CLIAparser/CLIArgumentParser.h"
#include "../XMLparser/xmlparser.h"
#include "Controller.h"

//API
//=========================================================================================

void Game::end(){
    on = false;
    LogManager::logDebug("señal de fin de programa emitida");
}

bool Game::isOn(){
    return on;
}

void Game::pauseResumeMusic(){
    if (Mix_PausedMusic() == 1){
        Mix_ResumeMusic();
        std::cerr<< "Reanudando Musica"<<std::endl;
    }
    else {
        Mix_PauseMusic();
        std::cerr<< "Pausando Musica"<<std::endl;
    }
}


//INIT
//=========================================================================================

void Game::initConfig() {
    string pathToConfigFile = CLIArgumentParser::getInstance().getPathToConfigFileName();

    XMLParser xmlParser;
    this->config = xmlParser.parse(pathToConfigFile);
}

void Game::initController() {
    controller = new Controller(this);
}

void Game::initSceneDirector() {
    sceneDirector = new SceneDirector(controller,config);

    LogManager::logDebug("[INIT]: creado el Scene Director");
    LogManager::logDebug("=======================================");
}

//DESTROY
//=========================================================================================

void Game::baseClassFreeMemory(){
    delete(controller);
    controller = nullptr;
    delete(config);
    config = nullptr;
    Mix_CloseAudio();
    SDL_DestroyWindow(this->window);
    SDL_DestroyRenderer(this->renderer);
    Mix_CloseAudio();
    SDL_Quit();
}