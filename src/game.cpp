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
    level1(10,15,10,width,heigth);

    Events event(this, character);
    //loop hasta que se aprete ESC o click en (X)
            /* Veo qu se esta apretando */
       while(isRunning){
            isRunning=!(event.keyboard_event());
        //    event.second_event();
        // event.second_event();
            /* Limpio la pantalla */    
            SDL_RenderClear( _gwindow->render );
            
            /* Actualizo la imagen */
            back->updateImage();
            middle->updateImage();
            floor->updateImage();

            /* Barriles con pos y menor a pj*/
            for (int i = 0; i < barriles.size();i++){
                if(character->GetPosY() >= barriles[i]->GetPosY()){
                    barriles[i]->updateImage();
            }
            }
            /* cody se actualiza a lo ultimo */
            character->updateImage();

            /* Barriles con pos y mayor a pj */
            for (int i = 0; i < barriles.size();i++){
                if(character->GetPosY() < barriles[i]->GetPosY()){
                    barriles[i]->updateImage();
            }
            /* Estoy recorriendo 2 veces el mismo vector para poner 
            cosas que estan detras de cody detras, ¿es necesario? */
            }

            /* Refresco la pantalla con nueva posicion */

            _gwindow->updateWindow();
            

            current = 1000/(-fps_last+SDL_GetTicks());// No 
            fps_last =SDL_GetTicks();//                   Son
            fpsChanged(current);///                      Importantes*/
        }
            
    this->~Game(); 
}

Game::~Game()
{
    //limpio vectores de escenario
    g1.clear();
    g2.clear();
    floor->~Background();
  //  delete(floor);
    back->~Far_background();
   // delete(middle);
   middle->~Far_background();
   // delete(back);
    character->~Character();
 //   delete(character);
    (_gwindow)->~Window();
    delete(_gwindow);
    SDL_Quit();
};

void Game::reboot(int width, int heigth){
//creo cosas del lvl 1
    SDL_SetRenderDrawColor(_gwindow->render, 0, 0, 0, 255);
    SDL_Rect rectangle;
    rectangle.x = 0;
    rectangle.y = 0;
    rectangle.w = 800;
    rectangle.h = 600;
    SDL_RenderClear( _gwindow->render );
    SDL_RenderFillRect(_gwindow->render, &rectangle);
    _gwindow->updateWindow();
    SDL_RenderClear( _gwindow->render );
    SDL_Delay(1000);
    g1.clear();
    g2.clear();
    floor->~Background();

    back->~Far_background();

   middle->~Far_background();

    character->~Character();

    level1(10,15,13,800,600);
    SDL_Delay(1000);    

};

void Game::move_all(){
//Actualiza posicion de todo menos de cody, en orden.
   back->move();
   
   middle->move();
   
   floor->move();
   
  for (int i = 0; i < barriles.size();i++){
       barriles[i]->move();
   }
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
    //le aviso a los barriles que ya no se muevan al llegar
    //cody al final de la pantalla
    for (int i = 0; i < barriles.size();i++){
        barriles[i]->moverse=false;
    }
}

void Game::level1(int enemy, int objetos, int armas,int width,int heigth){

    /* Background */
    g1.push_back("Sprites/FF_Stage4_floor1.png");
    g1.push_back("Sprites/FF_Stage4_floor2.png");
    g1.push_back("Sprites/FF_Stage4_floor3.png");
    g1.push_back("Sprites/FF_Stage4_floor4.png");
    g1.push_back("Sprites/FF_Stage4_floor5.png");
    g1.push_back("Sprites/FF_Stage4_floor6.png");
    /* Far Background */
    g2.push_back("Sprites/FF_Stage4_back12.png");
    g2.push_back("Sprites/FF_Stage4_back2.png");
    g2.push_back("Sprites/FF_Stage4_back3.png");
    g2.push_back("Sprites/FF_Stage4_back4.png");
    g2.push_back("Sprites/FF_Stage4_back5.png");
    g2.push_back("Sprites/FF_Stage4_back6.png");
    /* Middle Background */
    gmiddle.push_back("Sprites/barcos0.png");
    gmiddle.push_back("Sprites/barcos1.png");
    gmiddle.push_back("Sprites/barcos0.png");
    gmiddle.push_back("Sprites/barcos1.png");
    gmiddle.push_back("Sprites/barcos0.png");
    gmiddle.push_back("Sprites/barcos1.png");

    /* Creo 15 Barriles  -->*/
    int pos_x, pos_y;
    srand(time(NULL));
    /* posiciones del barril aleatoria en el rango del suelo */
    for (int  i = 0; i < objetos; i++)
    {
        pos_x =rand()%20001;
        pos_y = 120 +rand() % (201 - 120);
        barriles.push_back(new Object("Sprites/barril.png",pos_x, pos_y,_gwindow->render,width,heigth));
    }
            back = new Far_background(g2,heigth,width,_gwindow->render, 0.375);
    middle = new Far_background(gmiddle,heigth,width,_gwindow->render, 1.5);
    floor = new Background(g1,heigth,width,_gwindow->render, this,3);   
    character = new Character(width,heigth,_gwindow->render);
}