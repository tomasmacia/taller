#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "game.h"
#include "events.h"
#include "character.h"
#include <stdlib.h>
#include <time.h>
#include <algorithm>

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
   _gwindow= new Window("Final Fight",width,heigth);
};

void Game::UpdateAtras(vector <Enemy*> vector) {
     for (int i = 0; i < vector.size();i++){
        if(character->GetPosY() >= vector[i]->GetPosY()){
            vector[i]->updateImage();
        }
    }
}


void Game::UpdateDelante(vector <Enemy*> vector) {
     for (int i = 0; i < vector.size();i++){
        if(character->GetPosY() < vector[i]->GetPosY()){
            vector[i]->updateImage();
        }
    }
}


void Game::runLoop(int width, int heigth)
{
    Uint32 fps_last = SDL_GetTicks();
    Uint32 current;
    level1(10,10,10,10,10,width,heigth);

    Events event(this, character);
    //loop hasta que se aprete ESC o click en (X)
            /* Veo qu se esta apretando */
       while(isRunning){
            isRunning=!(event.keyboard_event());
            /* Limpio la pantalla */    
            SDL_RenderClear( _gwindow->render );
            
            /* Actualizo la imagen */
            back->updateImage();
     //       middle->updateImage();
            floor->updateImage();
            
             /* Enemigos con pos y menor a pj */
            UpdateAtras(enemigos);            
            
            /* obj_escenario con pos y menor a pj*/
            for (int i = 0; i < obj_escenario.size();i++){
                if(character->GetPosY() > obj_escenario[i]->GetPosY()){
                    obj_escenario[i]->updateImage();
                }
            }

            /* cody se actualiza donde necesite */
            character->updateImage();

            /* obj_escenario con pos y mayor a pj */
            for (int i = 0; i < obj_escenario.size();i++){
                if(character->GetPosY() <= obj_escenario[i]->GetPosY()){
                    obj_escenario[i]->updateImage();
                }
            }
           
           /* Enemigos con pos y mayor a pj */

           UpdateDelante(enemigos);
            
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
    gmiddle.clear();
    gfront.clear();
    g1.clear();
    g2.clear();    
    obj_escenario.clear();
    enemigos.clear();
    floor->~Background();
    back->~Background();
  //  middle->~Background();
    front->~Background();
    character->~Character();
    (_gwindow)->~Window();
    delete(_gwindow);
    SDL_Quit();
};


void Game::move_all(){
//Actualiza posicion de todo menos de cody, en orden.
   back->move();
   
 //  middle->move();
   
   floor->move();

  for (int i = 0; i < obj_escenario.size();i++){
       obj_escenario[i]->move();
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
    //le aviso a los obj_escenario que ya no se muevan al llegar
    //cody al final de la pantalla
    for (int i = 0; i < obj_escenario.size();i++){
        obj_escenario[i]->moverse=false;
    }
    for (int i = 0; i < enemigos.size();i++){
        enemigos[i]->moverse=false;
    }
}


void Game::level1(int enemy, int cajas,int barril, int tubos,int knifes,int width,int heigth){

    /* Background */
    g1.push_back("resources/sprites/FF_Stage4_floor1.png");
    g1.push_back("resources/sprites/FF_Stage4_floor2.png");
    g1.push_back("resources/sprites/FF_Stage4_floor3.png");
    g1.push_back("resources/sprites/FF_Stage4_floor4.png");
    g1.push_back("resources/sprites/FF_Stage4_floor5.png");
    g1.push_back("resources/sprites/FF_Stage4_floor6.png");
    /* Far Background */
    g2.push_back("resources/sprites/FF_Stage4_back1.png");
    g2.push_back("resources/sprites/FF_Stage4_back2.png");
    g2.push_back("resources/sprites/FF_Stage4_back3.png");
    g2.push_back("resources/sprites/FF_Stage4_back4.png");
    g2.push_back("resources/sprites/FF_Stage4_back5.png");
    g2.push_back("resources/sprites/FF_Stage4_back6.png");
    /* Middle Background */
  /*  gmiddle.push_back("resources/sprites/barcos0.png");
    gmiddle.push_back("resources/sprites/barcos1.png");
    gmiddle.push_back("resources/sprites/barcos0.png");
    gmiddle.push_back("resources/sprites/barcos1.png");
    gmiddle.push_back("resources/sprites/barcos0.png");
    gmiddle.push_back("resources/sprites/barcos1.png");*/
    /* Postes */
    gfront.push_back("resources/sprites/FF_Stage4_overlay1.png");
    gfront.push_back("resources/sprites/FF_Stage4_overlay2.png");
    gfront.push_back("resources/sprites/FF_Stage4_overlay3.png");
    gfront.push_back("resources/sprites/FF_Stage4_overlay4.png");
    gfront.push_back("resources/sprites/FF_Stage4_overlay5.png");
    gfront.push_back("resources/sprites/FF_Stage4_overlay6.png");

/* Creo objetos */
    int pos_x, pos_y;
    srand(time(NULL));
    /* posiciones del barril aleatoria en el rango del suelo */
    for (int  i = 0; i < barril; i++)
    {
        pos_x =rand()%(20001 );
        pos_y = 120 +rand() % (201 - 120);
        obj_escenario.push_back(new Object("resources/sprites/barril.png",pos_x, pos_y,_gwindow->render,width,heigth));
    }
    /* posiciones del cajas aleatoria en el rango del suelo */
    for (int  i = 0; i < cajas; i++)
    {
        pos_x =rand()%(20001);
        pos_y = 120 +rand() % (201 - 120);
        obj_escenario.push_back(new Object("resources/sprites/caja.png",pos_x, pos_y,_gwindow->render,width,heigth));
    }
    /* posiciones del tubos aleatoria en el rango del suelo */
    for (int  i = 0; i < tubos; i++)
    {
        pos_x =rand()%(20001);
        pos_y = 120 +rand() % (201 - 120);
        obj_escenario.push_back(new Object("resources/sprites/tube.png",pos_x, pos_y,_gwindow->render,width,heigth));
    }
    /* posiciones del cuchillos aleatoria en el rango del suelo */
    for (int  i = 0; i < knifes; i++)
    {
        pos_x =rand()%(20001);
        pos_y = 120 +rand() % (201 - 120);
        obj_escenario.push_back(new Object("resources/sprites/knife1.png",pos_x, pos_y,_gwindow->render,width,heigth));
    }

    /*  Sort por pos Y de objetos*/
    sort(obj_escenario.begin(), obj_escenario.end(),[](Object* i1, Object* i2){return (i1->GetPosY() < i2->GetPosY());});

   
    /* posiciones de los enemigos aleatorios en el rango del suelo */
    for (int i=0; i < enemy; i++)
    {
        pos_x = -1000 + rand()%(20001 + 1000);
        pos_y = 120 +rand() %(201 - 120);
        enemigos.push_back(new Enemy("resources/sprites/enemy_walk.png",pos_x, pos_y, _gwindow->render, width, heigth));
    }
     /*  Sort por pos Y*/
    sort(enemigos.begin(), enemigos.end(),[](Enemy* i1, Enemy* i2){return (i1->GetPosY() < i2->GetPosY());});
    
    //solo existe una clase back, a los backs de fondo no les sirve pasarle game pero
    //se los paso por paja, para no hacer otro constructor. Solo el de lvl 1 usa el game para
    // avisar que se llego al final del escenario.
    // se le pasa los parametros de la ventana, el render y la velocidad con la que se mueve
    // y el lvl de background que es (1 es el mas cercano y 3 el lejano)
    back = new Background(g2,heigth,width,_gwindow->render, this, 0.063,3);//0.063
   // middle = new Background(gmiddle,heigth,width,_gwindow->render,this, 0.25,3);
    floor = new Background(g1,heigth,width,_gwindow->render, this,0.5, 1);  
    front =  new Background(gfront,heigth,width,_gwindow->render, this,0.5, 4);
    character = new Character(this,width,heigth,_gwindow->render);

}

void Game::level2(int enemy, int cajas,int barril, int tubos,int knifes,int width,int heigth){


  /*  // Coloco pantalla en rojo y espero 1 sec
    SDL_SetRenderDrawColor(_gwindow->render, 255, 0, 0, 255);
    SDL_Rect rectangle;
    rectangle.x = 0;
    rectangle.y = 0;
    rectangle.w = width;
    rectangle.h = heigth;
    SDL_RenderFillRect(_gwindow->render, &rectangle);
    _gwindow->updateWindow();
    SDL_Delay(1000);



    floor->~Background();
    back->~Background();
  //  middle->~Background();
    front->~Background();*/

    /* Background */
    g1.push_back("resources/sprites/Final_Fight3-1.png");
    g1.push_back("resources/sprites/Final_Fight3-2.png");
    g1.push_back("resources/sprites/Final_Fight3-3.png");
    /* Far Background */
    g2.push_back("resources/sprites/background1-1.png");
    g2.push_back("resources/sprites/background1-2.png");

    /* Middle Background */
  /*  gmiddle.push_back("resources/sprites/barcos0.png");
    gmiddle.push_back("resources/sprites/barcos1.png");
    gmiddle.push_back("resources/sprites/barcos0.png");
    gmiddle.push_back("resources/sprites/barcos1.png");
    gmiddle.push_back("resources/sprites/barcos0.png");
    gmiddle.push_back("resources/sprites/barcos1.png");*/
    /* valla*/
    gfront.push_back("resources/sprites/front.png");
    gfront.push_back("resources/sprites/front2.png");
    gfront.push_back("resources/sprites/front3.png");



    back = new Background(g2,heigth,width,_gwindow->render, this, 0.13,3);
  //  middle = new Background(gmiddle,heigth,width,_gwindow->render,this, 0.25,3);
    floor = new Background(g1,heigth,width,_gwindow->render, this,0.5, 1);  
    front =  new Background(gfront,heigth,width,_gwindow->render, this,0.6, 4);
    character = new Character(this,width,heigth,_gwindow->render);
}