#include "Game.h"
#include "../LogLib/LogManager.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>
#include <algorithm>
#include "../parser/CLIArgumentParser.h"
#include "../parser/xmlparser.h"
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

void Game::initSDL() {
    if( SDL_Init(SDL_INIT_VIDEO) == 0 ) {
        if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
            LogManager::logError("Fallo SDL_Image");
        }

        int windowWidth = this->config->screenResolution.width;
        int windowHeight = this->config->screenResolution.height;

        this->window = SDL_CreateWindow("Final Fight", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, 0);
        this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_PRESENTVSYNC);
    }
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY,MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS,4098);
    Mix_AllocateChannels(100); //100 por las dudas

    if (this->window == nullptr || this->renderer == nullptr) {
        this->on = false;
        LogManager::logError("SDL no pudo inicializarse");
    }
}

//DESTROY
//=========================================================================================

void Game::baseClassFreeMemory(){
    delete(controller);
    controller = nullptr;
    delete(config);
    config = nullptr;
    SDL_DestroyWindow(this->window);
    SDL_DestroyRenderer(this->renderer);
    Mix_CloseAudio();
    SDL_Quit();
}

//SOUND
//===============================

void Game::init_music(){
    music = Mix_LoadMUS("resources/sfx/Game/fondo.mp3");
    sound1 = Mix_LoadWAV("resources/sfx/Game/kick.mp3");
    
    Mix_PlayMusic(music,-1);
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

void Game::close_music(){
    Mix_FreeMusic(music);
    Mix_CloseAudio();
}

void Game::sound(){

    Mix_PlayChannel(2,sound1,0);
}