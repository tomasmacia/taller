#include <time.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "game.h"

//CONSTRUCTOR & DESTRUCTOR
Game::Game(int width, int heigth)
{
    /*Los numeros magicos en este metodo no se extienen por fuera
    de esta metodo y surgen de a ojo ver que parametros dan el
    mejor acabado visual*/
    
    _width = width;
    _height = heigth;

    _maxY = _height; //SDL mide el Y = 0 desde arriba y aumenta hacia abajo
    _minY = 470;       

    _window = new Window(GAME_NAME,_width,_height);
    _renderer = _window->getRenderer();

    _background = new Background(_renderer, _width,_height);
    initCharacter();
    _eventHandler = new EventHandler(this,_character);
    intializeGameObjects();
    _background->setGameObjects(&_entities);
}

Game::~Game(){
    for (int i = 0; i < _entities.size();i++){
            delete(_entities.at(i));
        }
    delete(_background);
    delete(_character);
    delete(_window);
    delete(_eventHandler);
    std::cout <<"memoria liberada" << "\n";
}

//PUBLIC
void Game::handleInput(){
    _eventHandler->handleAllEventsInQueue();
}

void Game::update()
{
    _window->clear();
    _background->updateImage();

    /* Barriles que estan mas al fondo que cody*/
    for (int i = 0; i < _entities.size();i++){
        if(_character->getY() >= _entities[i]->getY()){
            _entities[i]->updateImage();
        }
    }
    _character->update();

    /* Barriles que estan mas cerca de la pantalla que cody*/
    for (int i = 0; i < _entities.size();i++){
        if(_character->getY() < _entities[i]->getY()){
            _entities[i]->updateImage();
        }
    }
}

void Game::display(){
    _window->display();
}

void Game::move_all(){
    _background->applyHorizontalLeftShift(); //mueve tambien lo que esta sobre el background
}

bool Game::isClosed(){
    return !isRunning;
}

void Game::close(){
    isRunning = false;
    //avisar al logger
}

//PRIVATE
void Game::intializeGameObjects(){
    /*Los numeros magicos en este metodo no se extienen por fuera
    de esta metodo y surgen de a ojo ver que parametros dan el
    mejor acabado visual*/

    float pos_x, pos_y;
    srand(time(NULL));
    /* posiciones del barril aleatoria en el rango del suelo */
    for (int  i = 0; i < BARREL_AMOUNT; i++)
    {
        pos_x =rand() % (int)(_background->getWidth());
        pos_y = (_minY) + rand() % (int)(_maxY -_minY);
        Barrel* barrel = new Barrel(_renderer,pos_x,pos_y,0.8,_maxY,_minY,true);
        _entities.push_back(barrel);
    }
}

void Game::initCharacter(){
    /*Los numeros magicos en este metodo no se extienen por fuera
    de esta metodo y surgen de a ojo ver que parametros dan el
    mejor acabado visual*/

    float x = _width/2;
    float y = (_maxY + _minY)/2;
    std::cout <<"y: "<< y << "\n";
    std::cout <<"_maxY: "<< _maxY << "\n";
    std::cout <<"_minY: "<< _minY << "\n";

    _character = new Character(_renderer, x, y, 0.8,_maxY,_minY,false);
}
/*
// Copiado del de SDLTest, para ver fps(creo)
void Game::fpsChanged(int fps){

    char szFps[128];
    sprintf(szFps,"%s: %d FPS","Final Figth",fps);

    SDL_SetWindowTitle(_window->getWindow(), szFps);
}
*/
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