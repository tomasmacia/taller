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
    Game(int width, int heigth);
 /*Destructor*/
    ~Game();

    void move_all();
    void pj_in_final();
    bool isClosed();
    void runLoop();

private:
    void initialize(int width, int heigth);
    void allCreator(int width, int heigth);
    void fpsChanged(int fps);
    void level1();
};
#endif