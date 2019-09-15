#include <game.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "events.h"
#include "character.h"


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
    /*Coloco pantalla en rojo y espero 1 sec
    SDL_SetRenderDrawColor(_gwindow->render, 255, 0, 0, 255);
    SDL_Rect rectangle;
    rectangle.x = 0;
    rectangle.y = 0;
    rectangle.w = width;
    rectangle.h = heigth;
    SDL_RenderFillRect(_gwindow->render, &rectangle);
    _gwindow->updateWindow();
    SDL_Delay(1000);*/

    allCreator(width,heigth);
    Events event(this, character);
    //loop hasta que se aprete ESC o click en (X)
    while (isRunning)
    {   isRunning = !(event.keyboard_event());
        SDL_RenderClear( _gwindow->render );
        back->updateImage();
        floor->updateImage();
        //barril ->updateImage();
        character->updateImage();  
        _gwindow->updateWindow();

        
        current = 1000/(-fps_last+SDL_GetTicks());// No 
        fps_last =SDL_GetTicks();//                   Son
        fpsChanged(current);///                      Importantes*/
    }
    this->~Game(); 
};

Game::~Game()
{
    floor->~Background();
    delete(floor);
    back->~Far_background();
    delete(back);
    character->~Character();
    delete(character);
    (_gwindow)->~Window();
    delete(_gwindow);
    SDL_Quit();
};

void Game::allCreator(int width, int heigth){

    //cosas del lvl 1
    back = new Far_background("Sprites/FF_Stage4_back1.png",heigth,width,_gwindow->render);
    floor = new Background("Sprites/FF_Stage4_floor1.png",heigth,width,_gwindow->render, this);   
    character = new Character("Sprites/cody.png",width,heigth,_gwindow->render);
    //barril= new Object("Sprites/barril.png",width,heigth,_gwindow->render);
};

void Game::move_all(){
//Actualiza posicion de todo menos de cody, en orden.
   back->move();
   floor->move();
 //  barril->move();

}
// Copiado del de SDLTest, para ver fps(creo)
void Game::fpsChanged(int fps){

    char szFps[128];
    sprintf(szFps,"%s: %d FPS","Final Figth",fps);
    SDL_SetWindowTitle(_gwindow->_window, szFps);
}

void Game::pj_in_final(){
    /* Si llegue al final de pantalla, el jugador es libre de moverse
    por toda la pantalla. Le modifico el limite vertical. */
    character->change_limits();
}
