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
    level1(2,15,10,width,heigth);

    Events event(this, character);
    //loop hasta que se aprete ESC o click en (X)
            /* Veo qu se esta apretando */
       while(isRunning){
            isRunning=!(event.keyboard_event());
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
            /* Enemigos con pos y menor a pj */
            for (int i = 0; i < enemigos.size();i++){
                if(character->GetPosY() >= enemigos[i]->GetPosY()){
                    enemigos[i]->updateImage();
            }
            }
            /* cody se actualiza a lo ultimo */
            character->updateImage();

            /* Barriles con pos y mayor a pj */
            for (int i = 0; i < barriles.size();i++){
                if(character->GetPosY() < barriles[i]->GetPosY()){
                    barriles[i]->updateImage();
            }
            /* Enemigos con pos y mayor a pj */
            for (int i = 0; i < enemigos.size();i++){
                if(character->GetPosY() >= enemigos[i]->GetPosY()){
                    enemigos[i]->updateImage();
            }
            }
            /* Estoy recorriendo 2 veces el mismo vector para poner 
            cosas que estan detras de cody detras, ¿es necesario? */
            }
            front->updateImage();
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
    back->~Background();
   // delete(middle);
   middle->~Background();
   // delete(back);
    character->~Character();
 //   delete(character);
    (_gwindow)->~Window();
    delete(_gwindow);
    SDL_Quit();
};


void Game::move_all(){
//Actualiza posicion de todo menos de cody, en orden.
   back->move();
   
   middle->move();
   
   floor->move();
   
  for (int i = 0; i < barriles.size();i++){
       barriles[i]->move();
   }

   for (int i = 0; i < enemigos.size(); i++){
       enemigos[i]->move();
   }

   front->move();
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
    for (int i = 0; i < enemigos.size();i++){
        enemigos[i]->moverse=false;
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
    g2.push_back("Sprites/FF_Stage4_back1.png");
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

    gfront.push_back("Sprites/FF_Stage4_overlay1.png");
    gfront.push_back("Sprites/FF_Stage4_overlay2.png");
    gfront.push_back("Sprites/FF_Stage4_overlay3.png");
    gfront.push_back("Sprites/FF_Stage4_overlay4.png");
    gfront.push_back("Sprites/FF_Stage4_overlay5.png");
    gfront.push_back("Sprites/FF_Stage4_overlay6.png");

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

    /* posiciones de los enemigos aleatorios en el rango del suelo */
    for (int i=0; i < enemy; i++){
        pos_x = rand()%20001;
        pos_y = 120 +rand() %(201 - 120);
        enemigos.push_back(new Enemy("Sprites/enemy.png",pos_x, pos_y, _gwindow->render, width, heigth));
    }

    //solo existe una clase back, a los backs de fondo no les sirve pasarle game pero
    //se los paso por paja, para no hacer otro constructor. Solo el de lvl 1 usa el game para
    // avisar que se llego al final del escenario.
    // se le pasa los parametros de la ventana, el render y la velocidad con la que se mueve
    // y el lvl de background que es (1 es el mas cercano, 2 el del medio y 3 el lejano)
    back = new Background(g2,heigth,width,_gwindow->render, this, 0.0882,3);
    middle = new Background(gmiddle,heigth,width,_gwindow->render,this, 0.35,3);
    floor = new Background(g1,heigth,width,_gwindow->render, this,0.7, 1);  
    front =  new Background(gfront,heigth,width,_gwindow->render, this,0.7, 1);
    character = new Character(this,width,heigth,_gwindow->render);
}