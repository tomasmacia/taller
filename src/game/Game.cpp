#include <iterator>
#include <SDL2/SDL.h>
#include <iostream>
#include <unistd.h>
#include <chrono>

#include "Game.h"
#include "GameObject.h"
#include "LevelBuilder.h"
#include "../parser/CLIArgumentParser.h"
#include "../parser/xmlparser.h"
#include "../parser/config/config.h"
#include "../window.h"
#include "../LogLib/DebugLogger.h"
#include "../LogLib/InfoLogger.h"
#include "../LogLib/ErrorLogger.h"
#include "../LogLib/LogManager.h"
#include "../LogLib/Logger.h"


bool endGame = false;

Game* Game::instance = nullptr;

Game* Game::getInstance() {
    if (instance == nullptr) {
        instance = new Game();
    }

    return instance;
}

void Game::init() {
    this->gameFinished = false;
    this->initConfig();
    //this->initLogManager();
    this->initSDL();
}

void Game::initConfig() {
    string defaultLogType = CLIArgumentParser::getInstance()->getDefaultLoggerLevel();
    string pathToConfigFile = CLIArgumentParser::getInstance()->getPathToConfigFileName();

    XMLParser xmlParser;
    this->config = xmlParser.parse(pathToConfigFile);
}

void Game::initLogManager() {
    Logger *logger;
    if (config->loggerLevel == "DEBUG") {
        logger = new DebugLogger();
    } else if (config->loggerLevel == "INFO") {
        logger = new InfoLogger();
    } else {
        logger = new ErrorLogger();
    }

    // TODO: por que estatico? singleton o normal. Asi lo podemos agregar al singleton de Game y consumirlo desde afuera
    LogManager::setStaticLogger(logger);
    LogManager::setStaticLogPath("test.txt");

}

void Game::initSDL() {
    if( SDL_Init(SDL_INIT_VIDEO) == 0 ) {
        this->window = SDL_CreateWindow("Final Fight", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
        this->renderer = SDL_CreateRenderer(this->window, -1, 0);
    }

    if (this->window == nullptr || this->renderer == nullptr) {
        this->gameFinished = true;
        std::cout << "SDL no pudo inicializarse" << endl;
    } else {
        SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255);
    }

}

void Game::destroy() {
    SDL_DestroyWindow(this->window);
    SDL_DestroyRenderer(this->renderer);
    SDL_Quit();
}


void Game::start(){
    using clock = std::chrono::high_resolution_clock;
    using milliseconds = std::chrono::milliseconds;
    using nanoseconds = std::chrono::nanoseconds;
    using std::chrono::duration_cast;

    auto start = clock::now(), end = clock::now();
    uint64_t diff = duration_cast<milliseconds>(end - start).count();

    auto accum_start = clock::now();

    LevelBuilder levelBuilder;
    this->hasNextLevel = true;

    while(this->isRunning()){
        this->hasNextLevel = levelBuilder.loadNext();

        start = clock::now();
        diff = duration_cast<milliseconds>(end - start).count();

        readInput();

        if(duration_cast<nanoseconds>(clock::now() - accum_start).count() >= 16666666){
            update();
            accum_start = clock::now();
        }

        render();

        end = clock::now();
    }
}

void Game::readInput(){
    Controller::reset();
    SDL_Event* e = new SDL_Event;
    while(SDL_PollEvent (e) != 0){
        if (e->type == SDL_QUIT){
            this->gameFinished = true;
        }
        if(e->type == SDL_KEYDOWN){
            switch(e->key.keysym.sym){
                case SDLK_UP:
                    Controller::pressUp();
                    break;
                case SDLK_DOWN:
                    Controller::pressDown();
                    break;

                case SDLK_LEFT:
                    Controller::pressLeft();
                    break;

                case SDLK_RIGHT:
                    Controller::pressRight();
                    break;
            }
        }
    }
}

void Game::update() {
    for (auto &gameObject : this->gameObjects) {
        gameObject->update();
    }
}

void Game::render() {
    SDL_RenderClear(this->renderer);
    for (auto &gameObject : this->gameObjects) {
        gameObject->render();
    }
    SDL_RenderPresent(this->renderer);
}

void Game::addGameObject(GameObject *gameObject) {
    this->gameObjects.push_back(gameObject);
}


bool Game::isRunning(){
    return !this->gameFinished;
}

