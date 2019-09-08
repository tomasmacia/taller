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

   _gwindow= new Window("Final Figth",640,480);
}

void Game::runLoop()
{
    //Creo Cuadrado
    Square square(100, 400, 300, 200, 0, 200, 255);
    //Creo evento
    Events event(&square);
    //loop hasta que se aprete ESC o click en (X)
    while (!event.keyboard_event())
    {
      //  std::cerr << "Loop.\n";
      //actualizo posicion de cuadrado y refresco la ventana
        (&square)->display();
        _gwindow->loadMedia();
    //    (_gwindow)->display();}
    this->~Game();
    }
}
    


Game::~Game()
{
    /*Quito ventana y cierro SDL*/
    (_gwindow)->~Window();
    SDL_Quit();

}

