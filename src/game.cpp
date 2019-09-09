#include <game.h>
#include <SDL2/SDL.h>
#include "cody.h"
#include "events.h"


Game::Game(int width, int heigth)
{
    initialize(width, heigth);
    runLoop(width, heigth);
}

void Game::initialize (int width, int heigth) 
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cerr << "Fallo SDL .\n";
    }
    std::cerr << "SDL.\n";

   _gwindow= new Window("Final Figth",width,heigth);
}

void Game::runLoop(int width, int heigth)
{
    //Creo Cuadrado/personaje
    Cody cody(0,width,heigth); //->Nose si el game deberia crear al pj.
    //Creo evento y paso pj para avisarle que debe moverse(si se debe hacer)
    Events event(&cody);
    _gwindow->frame_load(cody.getPosition());
    //loop hasta que se aprete ESC o click en (X)
    while (!event.keyboard_event())
    {
      //actualizo posicion de cuadrado y refresco la ventana
        _gwindow->frame_load(cody.getPosition());
    }
    //Destruyo y limpio lo usado. Salgo del juego.s
    this->~Game(); 
}

Game::~Game()
{
    /*Quito ventana y cierro SDL*/
    (_gwindow)->~Window();
    SDL_Quit();

}

