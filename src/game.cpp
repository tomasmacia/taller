#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>

#include "game.h"
#include "events.h"
#include "character.h"
#include "parser/CLIArgumentParser.h"
#include "parser/config/config.h"
#include "parser/xmlparser.h"
#include "LogLib/Logger.h"
#include "LevelBuilder.h"




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

    LogManager::setStaticLogger(this->logger);
    LogManager::setStaticLogPath("logs/log.txt");

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


void Game::UpdateAtras(vector<Game_Component*> vector) {
     for (auto &objeto : vector) {
        if (character->GetPosY() >= objeto->GetPosY()) {
            objeto->updateImage();
        }
    }
}


void Game::UpdateDelante(vector<Game_Component*> vector) {
     for (auto &objeto : vector) {
        if (character->GetPosY() < objeto->GetPosY()) {
            objeto->updateImage();
        }
    }
}


void Game::start() {
    Uint32 fps_last = SDL_GetTicks();
    Uint32 current;

    LevelBuilder levelBuilder;
    this->hasNextLevel = true;


    while (isRunning && hasNextLevel) {
        this->hasNextLevel = levelBuilder.loadNext();
        this->levelFinished = false;

        Events event(this, character);

        while (isRunning && hasNextLevel && !levelFinished) {
            isRunning = !(event.keyboard_event());
            /* Limpio la pantalla */
            SDL_RenderClear(renderer);

            /* Actualizo la imagen */
            far->updateImage();

            if (middle != nullptr) {
                middle->updateImage();
            }

            floor->updateImage();

            /* Enemigos con pos y menor a pj */
            UpdateAtras(obj_escenario);

            /* cody se actualiza a lo ultimo */
            character->updateImage();
            this->levelFinished = character->inFinal();

            /* Enemigos con pos y mayor a pj */

            UpdateDelante(obj_escenario);
            /* Estoy recorriendo 2 veces el mismo vector para poner
             * cosas que estan detras de cody detras, ¿es necesario? */

            overlay->updateImage();
            /* Refresco la pantalla con nueva posicion */

            SDL_RenderPresent(renderer);

            current = 1000 / ( (Uint32) SDL_GetTicks() - fps_last);
            fps_last = (Uint32) SDL_GetTicks();
            setWindowTitleWithFPS(current);
        }
    }
}


void Game::move_all(){
//Actualiza posicion de todo menos de cody, en orden.
   far->move();

   if (middle != nullptr) {
       middle->move();
   }

   floor->move();

   for (auto &objeto : obj_escenario) {
       objeto->move();
   }

   overlay->move();
}


void Game::setWindowTitleWithFPS(int fps){

    char szFps[128];
    sprintf(szFps, "%s: %d FPS", "Final Fight", fps);
    SDL_SetWindowTitle(window, szFps);
}

void Game::pj_in_final(){
    /* Si llegue al final de pantalla, el jugador es libre de moverse
    por toda la pantalla. Le modifico el limite vertical. */
    character->change_limits();
    //le aviso a los obj_escenario que ya no se muevan al llegar
    //cody al final de la pantalla
    for (auto &objeto : obj_escenario){
        objeto->moverse = false;
    }
}

void Game::destroyLevelObjects() {
    middleSprites.clear();
    overlaySprites.clear();
    floorSprites.clear();
    farSprites.clear();

    delete(floor);
    floor = nullptr;
    delete(middle);
    middle = nullptr;
    delete(far);
    far = nullptr;
    delete(overlay);
    overlay = nullptr;
    delete(character);
    character = nullptr;

    for (auto objeto : obj_escenario) {
        delete(objeto);
        objeto = nullptr;
    }

    obj_escenario.clear();
}

void Game::destroy() {
    destroyLevelObjects();

    delete(logger);
    logger = nullptr;

    SDL_DestroyWindow(this->window);
    SDL_DestroyRenderer(this->renderer);
    SDL_Quit();
}