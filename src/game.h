#ifndef GAME_H_
#define GAME_H_

#include "window.h"
#include "background.h"
#include "object.h"
#include <cstdlib>
#include <vector>
#include <iostream>
#include "object.h"
#include "game_component.h"

class Game
{
public:
/*Constructor*/
    Game(int width, int heigth);
 /*Destructor*/
    ~Game();   
    class Character* character;
    Background* back, *middle;
    Background* floor, *front;
    void move_all();
    void pj_in_final();
    bool isRunning = true;
    void level2(int enemy, int cajas,int barril, int tubos,int knifes,int width,int heigth);

private:


    void UpdateAtras(vector<Game_Component*> vector);
    void UpdateDelante(vector<Game_Component*> vector);
    Game_Component* _enemy;
    class Window* _gwindow;
    void initialize(int width, int heigth);
    void runLoop(int width, int heigth);
    void reboot(int width, int heigth);
    void fpsChanged(int fps);
    
    std::vector <string> g1;
    std::vector <string> gmiddle;
    std::vector <string> g2;
     std::vector <string> gfront;
    std::vector <Game_Component*> obj_escenario;
    std::vector <Game_Component*> enemigos;
    void level1(int enemy, int cajas,int barril, int tubos,int knifes,int width,int heigth);
;

};

#endif