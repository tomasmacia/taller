#include <SDL2/SDL.h>
#include "window.h"
#include "Game.h"

#ifndef SQUARE_H_
#define SQUARE_H_

class Square : public Displayable, public Updateable{

private:
    int _side;
    int _x,_y;
    int _r,_g,_b,_a;
    
    SDL_Rect _rectangle;

public:
    Square(int side, int x, int y, int r, int g, int b, int a);

    void display();
    void update();

    // void pollEvents(SDL_Event &event);
};

#endif