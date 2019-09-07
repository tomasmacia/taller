#include <game.h>
#include <SDL2/SDL.h>
#include "window.h"

Game::Game()
{
    initialize();
    runLoop();
}

void Game::initialize () 
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cerr << "Fallo SDL .\n";
    }
    std::cerr << "SDL.\n";

    _gwindow= new Window("Final Figth",640,480);
}

void Game::runLoop()
{
    _gwindow->loadMedia();
    while (!_gwindow->isClosed())
    {
      //  std::cerr << "Loop.\n";
        _gwindow->Keyboard();
    }
    this->~Game();
    
}

Game::~Game()
{
    /*Quito ventana y cierro SDL*/
    _gwindow->~Window();
    SDL_Quit();

}

