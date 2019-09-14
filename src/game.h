#ifndef GAME_H_
#define GAME_H_

#include "window.h"
#include "background.h"
#include "far_background.h"

class Game
{
public:
/*Constructor*/
    Game(int width, int heigth);
 /*Destructor*/
    ~Game();   
    class Character* character;
    Far_background* back;
    Background* floor;
    void move_all();

private:
    class Window* _gwindow;
    void initialize(int width, int heigth);
    void runLoop(int width, int heigth);
    void allCreator(int width, int heigth);
    void fpsChanged(int fps);
    bool isRunning = true;

};

#endif