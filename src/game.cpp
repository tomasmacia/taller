#include <game.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "events.h"
#include "far_background.h"
#include "character.h"
#include "background.h"


Game::Game(int width, int heigth)
{
    initialize(width, heigth);
    runLoop(width, heigth);
};

void Game::initialize (int width, int heigth) 
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cerr << "Fallo SDL .\n";
    }
    std::cerr << "SDL.\n";

   _gwindow= new Window("Final Figth",width,heigth);
 //  _image = IMG_Load("Sprites/FF_Stage4_floor.png");
};

void Game::runLoop(int width, int heigth)
{
    //loop hasta que se aprete ESC o click en (X)
    allCreator(width,heigth);
    Events event(this, character);
    while (!event.keyboard_event())
    {
        back->updateImage(_gwindow->_window);
        floor->updateImage(_gwindow->_window);
        character->updateImage(_gwindow->_window);
        _gwindow->updateWindow();
    }
    //Destruyo y limpio lo usado. Salgo del juego.
    this->~Game(); 
};

Game::~Game()
{
    delete(floor);
    delete(back);
    SDL_FreeSurface(_image);
    delete(character);
    (_gwindow)->~Window();
    delete(_gwindow);
    SDL_Quit();

};

void Game::allCreator(int width, int heigth){

    //cosas del lvl 1
    back = new Far_background("Sprites/FF_Stage4_back.png",heigth,width);
    floor = new Background("Sprites/FF_Stage4_floor1a.png",heigth,width);   
    character = new Character("Sprites/cody.png",width,heigth);
};

void Game::move_all(){
    back->move();
    floor->move();
}

