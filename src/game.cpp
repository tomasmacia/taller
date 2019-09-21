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

    _maxY = _height;
    _minY = _height * (1 - WALKABLE_BACKGROUND_PERCENTAGE);

    _window = new Window(GAME_NAME,_width,_height);
    _renderer = _window->getRenderer();

    _background = new Background(_renderer, _width,_height); 
    character = new Character("Sprites/cody.png",width,heigth,_renderer);
    intializeGameObjects();
    _background->setGameObjects(&_entities);
}

void Game::runLoop()
{
    Events event(this, character);

    /*
    while( SDL_PollEvent( &e ) != 0 ){
    }
    */
    isRunning = !(event.keyboard_event());  

    _window->clear();
    _background->updateImage();

    for (int i = 0; i < _entities.size();i++){
        _entities.at(i)->updateImage();
    }
    character->updateImage();
    _window->display();
}

Game::~Game(){
    for (int i = 0; i < _entities.size();i++){
            delete(_entities.at(i));
        }
    delete(_background);
    delete(character);
    delete(_window);
    std::cout <<"memoria liberada" << "\n";
}

//PUBLIC

void Game::move_all(){
    _background->applyHorizontalLeftShift(); //mueve tambien lo que esta sobre el background
}

bool Game::isClosed(){
    return !isRunning;
}

//PRIVATE
void Game::intializeGameObjects(){
    float pos_x, pos_y;
    srand(time(NULL));
    /* posiciones del barril aleatoria en el rango del suelo */
    for (int  i = 0; i < BARREL_AMOUNT; i++)
    {
        pos_x =rand() % (int)(_width * _background->getWidthScaleFactorScreenToNear());
        pos_y = (_minY) + rand() % (int)(_maxY -_minY - OFFSET);
        Barrel* barrel = new Barrel(_renderer,pos_x,pos_y,MIN_SCALE_FACTOR,_maxY,_minY);
        _entities.push_back(barrel);
    }
}

// Copiado del de SDLTest, para ver fps(creo)
void Game::fpsChanged(int fps){

    char szFps[128];
    sprintf(szFps,"%s: %d FPS","Final Figth",fps);

    SDL_SetWindowTitle(_window->getWindow(), szFps);
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