#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <algorithm>

#include "Game.h"
#include "Controller.h"
#include "Action.h"
#include "../parser/CLIArgumentParser.h"
#include "../parser/config/config.h"
#include "../parser/xmlparser.h"
#include "../LogLib/Logger.h"
#include "LevelBuilder.h"
#include "../utils/TimeUtils.h"




void Game::init() {
    //this->isRunning= false;
    this->initLogManager(CLIArgumentParser::getInstance().getDefaultLoggerLevel());
    this->initConfig();
    this->initLogManager(this->config->loggerLevel);
    this->initSDL();
}

void Game::initConfig() {
    string pathToConfigFile = CLIArgumentParser::getInstance().getPathToConfigFileName();

    XMLParser xmlParser;
    this->config = xmlParser.parse(pathToConfigFile);
}

void Game::initLogManager(string loggerLevel) {
    delete(this->logger);
    this->logger = nullptr;
    this->logger = LogManager::createLoggerFromLevel(loggerLevel);

    string currentTime = TimeUtils::getCurrentTime();
    std::replace(currentTime.begin(), currentTime.end(), ' ', '_');

    string logfilePath = "logs/log_" + currentTime + ".txt";

    LogManager::setStaticLogger(this->logger);
    LogManager::setStaticLogPath(logfilePath);

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

    if (this->window == nullptr || this->renderer == nullptr) {
        this->isRunning = false;
        LogManager::logError("SDL no pudo inicializarse");
    } else {
        this->isRunning = true;
        //SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255);
    }

}

void Game::initController() {
    this->controller = new Controller();
}

void Game::initECSManager() {
    this->manager = new Manager();
}


void Game::start() {
    Uint32 fps_last = SDL_GetTicks();
    Uint32 current;

    this->initECSManager();
    this->initController(); // instantiate out of constructor, since Controller uses Game::getInstance() and would create a deadlock

    LevelBuilder levelBuilder;
    this->hasNextLevel = true;


    while (isRunning && hasNextLevel) {
        this->hasNextLevel = levelBuilder.loadNext();
        this->levelFinished = false;

        while (isRunning && hasNextLevel && !levelFinished) {
            isRunning = isGameRunning();

            processInput();
            update();
            render();

            //current = 1000 / ( (Uint32) SDL_GetTicks() - fps_last);
            //fps_last = (Uint32) SDL_GetTicks();
            //setWindowTitleWithFPS(current);
        }
    }
}

bool Game::isGameRunning() { // TODO: implement when we have a proper gameloop input-update-render
    std::vector<Action> actions = controller->getInput();
    //return actions.empty() || std::find(actions.begin(), actions.end(), Action::QUIT) != actions.end();
    return true;
}

void Game::processInput() {
    controller->processInput();
}

void Game::update() {
    manager->refresh();
    manager->update();
}

void Game::render() {
    SDL_RenderClear(renderer);

    manager->render();

    SDL_RenderPresent(renderer);
}



void Game::setWindowTitleWithFPS(int fps){

    char szFps[128];
    sprintf(szFps, "%s: %d FPS", "Final Fight", fps);
    SDL_SetWindowTitle(window, szFps);
}


void Game::destroy() {

    delete(logger);
    logger = nullptr;

    SDL_DestroyWindow(this->window);
    SDL_DestroyRenderer(this->renderer);
    SDL_Quit();
}
