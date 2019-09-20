#ifndef GAME_H_
#define GAME_H_

#include "window.h"
#include "background.h"
#include "far_background.h"
#include "object.h"
#include <cstdlib>
#include <vector>
#include <iostream>
#include "object.h"

class Game
{
public:
/*Constructor*/
    Game(int width, int heigth);
 /*Destructor*/
    ~Game();   
    class Character* character;
    Far_background* back, *middle;
    Background* floor;
    void move_all();
    void pj_in_final();

private:
    class Window* _gwindow;
    void initialize(int width, int heigth);
    void runLoop(int width, int heigth);
    void reboot(int width, int heigth);
    void fpsChanged(int fps);
    bool isRunning = true;
    std::vector <string> g1;
    std::vector <string> gmiddle;
    std::vector <string> g2;
    std::vector <Object*> barriles;
    void level1(int enemy, int objetos, int armas,int heigth,int width);

};

#endif