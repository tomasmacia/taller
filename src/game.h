#ifndef GAME_H_
#define GAME_H_

#include <cstdlib>
#include <vector>
#include <iostream>
#include "object.h"
#include "window.h"
#include "background.h"
#include "far_background.h"
#include "object.h"

class Game
{
private:
    bool isRunning = true;

    int _width;
    int _height;

    class Character* character;
    Far_background* back;
    Background* floor;

    std::vector <string> g1;
    std::vector <string> g2;
    std::vector <Object*> barriles;

    class Window* _gwindow;

public:
/*Constructor*/
    Game(int width, int heigth);                //refactorizado
 /*Destructor*/
    ~Game();

    void runLoop();
    void move_all();
    void pj_in_final();
    bool isClosed();                            //agregado

private:
    void initialize();                          //refactorizado
    void allCreator(int width, int heigth);     //revisado (esta bastante bien)    
    void level1();                              //revisado (esta bastante bien)
    void fpsChanged(int fps);                   //revisado (esta bastante bien)
};
#endif