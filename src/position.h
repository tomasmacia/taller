#ifndef POSITION_H
#define POSITION_H
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "appearance.h"

class Position{

private:
    float _x;
    float _y;
    Appearance* _appearance;

public:
    Position(float x,float y,Appearance* appearance);

    void changeXBy(float amount);
    void changeYBy(float amount);

    float getX();
    float getY();
    
private:
};
#endif