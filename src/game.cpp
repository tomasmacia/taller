#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <time.h>

#include "game.h"
#include "events.h"
#include "character.h"
#include "parser/CLIArgumentParser.h"
#include "parser/config/config.h"
#include "parser/xmlparser.h"
#include "LogLib/Logger.h"



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


void Game::UpdateAtras(vector <Enemy*> vector) {
     for (int i = 0; i < vector.size();i++){
        if(character->GetPosY() >= vector[i]->GetPosY()){
            vector[i]->updateImage();
        }
    }
}


void Game::UpdateDelante(vector <Enemy*> vector) {
     for (int i = 0; i < vector.size();i++){
        if(character->GetPosY() < vector[i]->GetPosY()){
            vector[i]->updateImage();
        }
    }
}


void Game::start() {
    int width = this->config->screenResolution.width;
    int height = this->config->screenResolution.height;

    Uint32 fps_last = SDL_GetTicks();
    Uint32 current;
    level1(8,15,10,width,height);

    Events event(this, character);

    //loop hasta que se aprete ESC o click en (X)
    /* Veo qu se esta apretando */
    while(isRunning) {
        isRunning=!(event.keyboard_event());
        /* Limpio la pantalla */
        SDL_RenderClear(renderer);

        /* Actualizo la imagen */
        back->updateImage();
        middle->updateImage();
        floor->updateImage();
        /* Barriles con pos y menor a pj*/
        for (int i = 0; i < barriles.size();i++){
            if(character->GetPosY() >= barriles[i]->GetPosY()){
                barriles[i]->updateImage();
            }
        }
        /* Enemigos con pos y menor a pj */
        UpdateAtras(enemigos);

        /* cody se actualiza a lo ultimo */
        character->updateImage();

        /* Barriles con pos y mayor a pj */
        for (int i = 0; i < barriles.size();i++){
            if(character->GetPosY() < barriles[i]->GetPosY()){
                barriles[i]->updateImage();
            }
        }
        /* Enemigos con pos y mayor a pj */

        UpdateDelante(enemigos);
        /* Estoy recorriendo 2 veces el mismo vector para poner
         * cosas que estan detras de cody detras, ¿es necesario? */

        front->updateImage();
        /* Refresco la pantalla con nueva posicion */

        SDL_RenderPresent(renderer);

        current = 1000 / (SDL_GetTicks() - fps_last);
        fps_last = SDL_GetTicks();
        setWindowTitleWithFPS(current);
    }
}


void Game::move_all(){
//Actualiza posicion de todo menos de cody, en orden.
   back->move();
   
   middle->move();
   
   floor->move();

   for (auto& barril : barriles){
       barril->move();
   }

   for (auto& enemigo : enemigos){
       enemigo->move();
   }

   front->move();
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
    //le aviso a los barriles que ya no se muevan al llegar
    //cody al final de la pantalla

    for (auto& barril : barriles){
        barril->moverse=false;
    }

 /*   for (int i = 0; i < enemigos.size();i++){
        enemigos[i]->moverse=false;
    }*/
}

void Game::level1(int enemy, int objetos, int armas, int width, int heigth){

    /* Background */
    g1.push_back("resources/sprites/FF_Stage4_floor1.png");
    g1.push_back("resources/sprites/FF_Stage4_floor2.png");
    g1.push_back("resources/sprites/FF_Stage4_floor3.png");
    g1.push_back("resources/sprites/FF_Stage4_floor4.png");
    g1.push_back("resources/sprites/FF_Stage4_floor5.png");
    g1.push_back("resources/sprites/FF_Stage4_floor6.png");
    /* Far Background */
    g2.push_back("resources/sprites/FF_Stage4_back1.png");
    g2.push_back("resources/sprites/FF_Stage4_back2.png");
    g2.push_back("resources/sprites/FF_Stage4_back3.png");
    g2.push_back("resources/sprites/FF_Stage4_back4.png");
    g2.push_back("resources/sprites/FF_Stage4_back5.png");
    g2.push_back("resources/sprites/FF_Stage4_back6.png");
    /* Middle Background */
    gmiddle.push_back("resources/sprites/barcos0.png");
    gmiddle.push_back("resources/sprites/barcos1.png");
    gmiddle.push_back("resources/sprites/barcos0.png");
    gmiddle.push_back("resources/sprites/barcos1.png");
    gmiddle.push_back("resources/sprites/barcos0.png");
    gmiddle.push_back("resources/sprites/barcos1.png");

    gfront.push_back("resources/sprites/FF_Stage4_overlay1.png");
    gfront.push_back("resources/sprites/FF_Stage4_overlay2.png");
    gfront.push_back("resources/sprites/FF_Stage4_overlay3.png");
    gfront.push_back("resources/sprites/FF_Stage4_overlay4.png");
    gfront.push_back("resources/sprites/FF_Stage4_overlay5.png");
    gfront.push_back("resources/sprites/FF_Stage4_overlay6.png");

    /* Creo 15 Barriles  -->*/
    int pos_x, pos_y;
    srand(time(NULL));
    /* posiciones del barril aleatoria en el rango del suelo */
    for (int  i = 0; i < objetos; i++) {
        pos_x = (-1000) + rand() % (20001 - (-1000));
        pos_y = 120 + rand() % (201 - 120);
        barriles.push_back(new Object("resources/sprites/barril.png", pos_x, pos_y,renderer,width,heigth));
    }

    /* posiciones de los enemigos aleatorios en el rango del suelo */
    for (int i=0; i < enemy; i++) {
        pos_x = rand() % 20001;
        pos_y = 120 + rand() % (201 - 120);
        enemigos.push_back(new Enemy("resources/sprites/enemy_walk.png", pos_x, pos_y, renderer, width, heigth));
    }

    //solo existe una clase back, a los backs de fondo no les sirve pasarle game pero
    //se los paso por paja, para no hacer otro constructor. Solo el de lvl 1 usa el game para
    // avisar que se llego al final del escenario.
    // se le pasa los parametros de la ventana, el render y la velocidad con la que se mueve
    // y el lvl de background que es (1 es el mas cercano, 2 el del medio y 3 el lejano)
    back = new Background(g2, heigth, width, renderer, this, 0.063,3);
    middle = new Background(gmiddle, heigth, width, renderer, this, 0.25, 3);
    floor = new Background(g1, heigth, width, renderer, this,0.5, 1);
    front =  new Background(gfront, heigth, width, renderer, this,0.5, 4);
    character = new Character(this, width, heigth, renderer);
}

void Game::destroy() {
    //limpio vectores de escenario
    gmiddle.clear();
    gfront.clear();
    barriles.clear();
    enemigos.clear();
    g1.clear();
    g2.clear();
    floor->~Background();
    //  delete(floor);
    back->~Background();
    // delete(middle);
    middle->~Background();
    // delete(back);
    character->~Character();
    //   delete(character);

    delete logger;

    SDL_DestroyWindow(this->window);
    SDL_DestroyRenderer(this->renderer);
    SDL_Quit();
}