#include <game.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "events.h"
#include "far_background.h"
#include "character.h"
#include "background.h"
#define FPS_INTERVAL 1.0//


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
   _gwindow= new Window("Final Figth",width,heigth);
};

void Game::runLoop(int width, int heigth)
{
    Uint32 fps_last = SDL_GetTicks();
    Uint32 current;
    //loop hasta que se aprete ESC o click en (X)
    allCreator(width,heigth);
    Events event(this, character);
    while (!event.keyboard_event())
    {
        back->updateImage(_gwindow->_window);
        floor->updateImage(_gwindow->_window);
        character->updateImage(_gwindow->_window);
        _gwindow->updateWindow();
        current = 1000/(-fps_last+SDL_GetTicks());// No 
        fps_last =SDL_GetTicks();//                   Son
        fpsChanged(current);///                      Importantes
    }
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
    floor = new Background("Sprites/FF_Stage4_floor.png",heigth,width);   
    character = new Character("Sprites/cody.png",width,heigth);
};

void Game::move_all(){
//Actualiza posicion de todo menos de cody, en orden.
    back->move();
    floor->move();
}
// Copiado del de SDLTest, para ver fps(creo)
void Game::fpsChanged(int fps){

    char szFps[128];
    sprintf(szFps,"%s: %d FPS","Final Figth",fps);
    SDL_SetWindowTitle(_gwindow->_window, szFps);
}