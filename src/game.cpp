#include <game.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "events.h"
#include "character.h"
#include <stdlib.h>
#include <time.h>



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
            /* Veo qu se esta apretando */
    {   isRunning = !(event.keyboard_event());
            /* Actualizo la imagen */
        SDL_RenderClear( _gwindow->render );
        back->updateImage();
        floor->updateImage();
     /*   for (int i = 0; i = barriles.size();i++){
            barriles[i]->updateImage();
        }*/
        barril ->updateImage();
        b1->updateImage();
        b2->updateImage();
        b3->updateImage();
        b4->updateImage();
        b5->updateImage();

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
    delete(barril);
   // floor->~Background();
    delete(floor);
  //  back->~Far_background();
    delete(back);
    character->~Character();
    delete(character);
    (_gwindow)->~Window();
    delete(_gwindow);
    SDL_Quit();
};

void Game::allCreator(int width, int heigth){

    //cosas del lvl 1
    level1();
    back = new Far_background(g2,heigth,width,_gwindow->render);
    floor = new Background(g1,heigth,width,_gwindow->render, this);   
    character = new Character("Sprites/cody.png",width,heigth,_gwindow->render);
  /* barril de prueba */
    barril= new Object("Sprites/barril.png",500,245,_gwindow->render);
};

void Game::move_all(){
//Actualiza posicion de todo menos de cody, en orden.
   back->move();
   floor->move();
/*   for (int i = 0; i = barriles.size();i++){
       barriles[i]->move();
   }*/
    barril->move();
    b1->move();
    b2->move();
    b3->move();
    b4->move();
    b5->move();
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
    barril->moverse = false;
    b1->moverse = false;
    b2->moverse = false;
    b3->moverse = false;
    b4->moverse = false;
    b5->moverse = false;
}

void Game::level1(){
    /* Background */
    g1.push_back("Sprites/FF_Stage4_floor1.png");
    g1.push_back("Sprites/FF_Stage4_floor2.png");
    g1.push_back("Sprites/FF_Stage4_floor3.png");
    g1.push_back("Sprites/FF_Stage4_floor4.png");
    g1.push_back("Sprites/FF_Stage4_floor5.png");
    g1.push_back("Sprites/FF_Stage4_floor6.png");
    /* Far Background */
    g2.push_back("Sprites/FF_Stage4_back1.png");
    g2.push_back("Sprites/FF_Stage4_back2.png");
    g2.push_back("Sprites/FF_Stage4_back3.png");
    g2.push_back("Sprites/FF_Stage4_back4.png");
    g2.push_back("Sprites/FF_Stage4_back5.png");
    g2.push_back("Sprites/FF_Stage4_back6.png");
    /* Creo 5 Barriles  --> Error Core generado*/
    int pos_x, pos_y;
    srand(time(NULL));

    pos_x =rand()%20001;
    pos_y = 245 +rand() % (351 - 245);
    b1 = new Object("Sprites/barril.png",pos_x,pos_y,_gwindow->render);

    pos_x =rand()%22001;
    pos_y = 245 +rand() % (351 - 245);
    b2 = new Object("Sprites/barril.png",pos_x,pos_y,_gwindow->render);

    pos_x =rand()%22001;
    pos_y = 245 +rand() % (351 - 245);
    b3 = new Object("Sprites/barril.png",pos_x,pos_y,_gwindow->render);

    pos_x =rand()%22001;
    pos_y = 245 +rand() % (351 - 245);
    b4 = new Object("Sprites/barril.png",pos_x,pos_y,_gwindow->render);

    pos_x =rand()%22001;
    pos_y = 245 +rand() % (351 - 245);
    b5 = new Object("Sprites/barril.png",pos_x,pos_y,_gwindow->render);
    
    barriles.push_back(b1);
    barriles.push_back(b2);
    barriles.push_back(b3);
    barriles.push_back(b4);
    barriles.push_back(b5);
}