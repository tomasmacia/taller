#include <game.h>
#include <SDL2/SDL.h>
#include "square.h"
#include "events.h"


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

   _gwindow= new Window("Final Figth",1366,200);
}

void Game::runLoop()
{
    //Creo Cuadrado/personaje
    Square square(1, 0, 80, 200, 0, 200, 255);
    //Creo evento
    Events event(&square);
    _gwindow->loadFondo("Sprites/FF_Stage4_floor.png");
    //loop hasta que se aprete ESC o click en (X)
    while (!event.keyboard_event())
    {
      //actualizo posicion de cuadrado y refresco la ventana
        (&square)->display(_gwindow);
        _gwindow->loadFondo("Sprites/FF_Stage4_floor.png");
       (&square)->display(_gwindow);
    }
    this->~Game(); 
}

    


Game::~Game()
{
    /*Quito ventana y cierro SDL*/
    (_gwindow)->~Window();
    SDL_Quit();

}

