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

   _gwindow= new Window("Final Figth",277,198);
}

void Game::runLoop()
{
    //Creo Cuadrado/personaje
    Square square(1, 0, 80);
    //Creo evento y paso pj para avisarle que debe moverse(si se debe hacer)
    Events event(&square);
    _gwindow->frame_load(square.getPosition());
    //loop hasta que se aprete ESC o click en (X)
    while (!event.keyboard_event())
    {
      //actualizo posicion de cuadrado y refresco la ventana
        _gwindow->frame_load(square.getPosition());
    }
    //Destruyo y limpio lo usado. Salgo del juego.
    this->~Game(); 
}

    


Game::~Game()
{
    /*Quito ventana y cierro SDL*/
    (_gwindow)->~Window();
    SDL_Quit();

}

