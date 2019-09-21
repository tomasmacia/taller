#include <time.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "events.h"
#include "character.h"
#include "game.h"
#include "window.h"

//CONSTRUCTOR & DESTRUCTOR
Game::Game(int width, int heigth)
{
    _width = width;
    _height = heigth;
    initialize();
}

void Game::runLoop()
{
    Events event(this, character);
    isRunning = !(event.keyboard_event());  

    _gwindow->clear();
    _background->updateImage();

    for (int i = 0; i < _entities.size();i++){
        _entities.at(i)->updateImage();
    }
    character->updateImage();
    _gwindow->display();
}

Game::~Game(){
    for (int i = 0; i < _entities.size();i++){
            delete(_entities.at(i));
        }
    delete(_background);
    delete(character);
    delete(_gwindow);
}

//PUBLIC
void Game::move_all(){
    _background->applyHorizontalLeftShift();
}

bool Game::isClosed(){
    return !isRunning;
}

//PRIVATE
void Game::initialize() 
{
   _gwindow = new Window("Final Figth",_width,_height);
   _renderer = _gwindow->getRenderer();
    allCreator(_width,_height);
}

void Game::allCreator(int width, int heigth){
    intializeGameObjects();
    _background = new Background(_renderer,&_entities, _width,_height);   
    character = new Character("Sprites/cody.png",width,heigth,_renderer);
}

void Game::intializeGameObjects(){
    float pos_x, pos_y;
    srand(time(NULL));
    /* posiciones del barril aleatoria en el rango del suelo */
    for (int  i = 0; i < BARREL_AMOUNT; i++)
    {
        pos_x =rand()%20001;
        pos_y = 245 + rand() % (351 - 245);
        _entities.push_back(new Barrel(_renderer,pos_x,pos_y));
    }
}

// Copiado del de SDLTest, para ver fps(creo)
void Game::fpsChanged(int fps){

    char szFps[128];
    sprintf(szFps,"%s: %d FPS","Final Figth",fps);

    SDL_SetWindowTitle(_gwindow->getWindow(), szFps);
}


/*
void Game::pj_in_final(){
    //Si llegue al final de pantalla, el jugador es libre de moverse
    //por toda la pantalla. Le modifico el limite vertical.
    character->change_limits();
    //le aviso a los barriles que ya no se muevan al llegar
    //cody al final de la pantalla
    for (int i = 0; i < _entities->size();i++){
        _entities->at(i)->moverse=false;
    }
}*/