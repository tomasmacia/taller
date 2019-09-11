#ifndef GAME_H_
#define GAME_H_

#include "window.h"
#include "background.h"
#include "far_background.h"

class Game
{
public:
/*Constructor*/

    class Character* character;
    Far_background* back;
    Background* floor;


	Game(int width, int heigth);
    void move_all();

private:
SDL_Surface* _image;
    class Window* _gwindow;
    void initialize(int width, int heigth);
    void runLoop(int width, int heigth);
    void allCreator(int width, int heigth);
    
/*Destructor*/
    ~Game();
};

#endif