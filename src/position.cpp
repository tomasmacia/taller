#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "appearance.h"
#include "position.h"

//CONSTRUCTOR & DESTRUCTOR
Position::Position(float x,float y,Appearance* appearance) :
_x(x), _y(y), _appearance(appearance){}

Position::~Position(){}

//PUBLIC
void Position::changeXBy(float amount){
    _x = _x + amount;
    _appearance->setX(_x);
}

void Position::changeYBy(float amount){
    _y = _y + amount;
    _appearance->setY(_y);
}

float Position::getX(){
    return _x;
}

float Position::getY(){
    return _y;
}

//PRIVATE