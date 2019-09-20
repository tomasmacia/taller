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
    initialize();
}

void Game::runLoop()
{
    Uint32 fps_last = SDL_GetTicks();
    Uint32 current;

    Events event(this, character);
    //loop hasta que se aprete ESC o click en (X)
    while (isRunning)
            /* Veo qu se esta apretando */
    {   isRunning = !(event.keyboard_event());
        /* Limpio la pantalla */    
        SDL_RenderClear( _gwindow->getRenderer());
        
        /* Actualizo la imagen */
        _background->updateImage();
       for (int i = 0; i < barriles.size();i++){
            barriles[i]->updateImage();
        }
        /* cody se actualiza a lo ultimo */
        character->updateImage();

        /* Refresco la pantalla con nueva posicion */  
        _gwindow->showAll();

        current = 1000/(-fps_last+SDL_GetTicks());// No 
        fps_last =SDL_GetTicks();//                   Son
        fpsChanged(current);///                      Importantes*/
    }
 //   this->~Game(); 
}

Game::~Game()
{
    g1.clear();
    g2.clear();
    //borro barriles
    for (int i = 0; i < barriles.size();i++){
            barriles[i]->~Object();
            delete(barriles[i]);
        }
   // floor->~Background();
    delete(_background);
 //   character->~Character();
    delete(character);
    (_gwindow)->~Window();
    delete(_gwindow);
    SDL_Quit();
}

//PUBLIC
void Game::move_all(){
//Actualiza posicion de todo menos de cody, en orden.
   _background->move();
  for (int i = 0; i < barriles.size();i++){
       barriles[i]->move();
   }
}

bool Game::isClosed(){
    return !isRunning;
}

void Game::pj_in_final(){
    /* Si llegue al final de pantalla, el jugador es libre de moverse
    por toda la pantalla. Le modifico el limite vertical. */
    character->change_limits();
    //le aviso a los barriles que ya no se muevan al llegar
    //cody al final de la pantalla
    for (int i = 0; i < barriles.size();i++){
        barriles[i]->moverse=false;
    }
}

//PRIVATE
void Game::initialize() 
{
   _gwindow = new Window("Final Figth",_width,_height);
   _renderer = _gwindow->getRenderer();
   allCreator(_width,_height);
}

void Game::allCreator(int width, int heigth){
//creo cosas del lvl 1
    _entities = intializeEntities();
    //back = new Far_background(g2,heigth,width,_gwindow->getRenderer());
    _background = new Background(_renderer,_entities, _width,_height);   
    character = new Character("Sprites/cody.png",width,heigth,_gwindow->getRenderer());
}

vector<Entity>* Game::intializeEntities(){
    /* Creo 20 Barriles  -->*/
    int pos_x, pos_y;
    srand(time(NULL));
    /* posiciones del barril aleatoria en el rango del suelo */
    for (int  i = 0; i < 20; i++)
    {
        pos_x =rand()%20001;
        pos_y = 245 + rand() % (351 - 245);
        barriles.push_back(new Object("Sprites/barril.png",pos_x,pos_y,_gwindow->getRenderer()));
    }
}

// Copiado del de SDLTest, para ver fps(creo)
void Game::fpsChanged(int fps){

    char szFps[128];
    sprintf(szFps,"%s: %d FPS","Final Figth",fps);

    SDL_SetWindowTitle(_gwindow->getWindow(), szFps);
}