#ifndef GAME_H_
#define GAME_H_

#include "window.h"
#include "background.h"
#include "object.h"
#include <cstdlib>
#include <vector>
#include <iostream>
#include "object.h"
#include "enemy.h"

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

private:
    Enemy* _enemy;
    class Window* _gwindow;
    void initialize(int width, int heigth);
    void runLoop(int width, int heigth);
    void reboot(int width, int heigth);
    void fpsChanged(int fps);
    bool isRunning = true;
    std::vector <string> g1;
    std::vector <string> gmiddle;
    std::vector <string> g2;
     std::vector <string> gfront;
    std::vector <Object*> barriles;
    std::vector <Enemy*> enemigos;
    void level1(int enemy, int objetos, int armas,int heigth,int width);

};

#endif