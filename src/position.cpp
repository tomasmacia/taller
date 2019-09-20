#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "square.h"
#include "position.h"

//CONSTRUCTOR & DESTRUCTOR
Position::Position(float x,float y,Square* square) :
_x(x), _y(y), _square(square){}

Position::~Position(){}

//PUBLIC
void Position::changeXBy(float amount){
    _x = _x + amount;
    _square->setX(_x);
}

void Position::changeYBy(float amount){
    _y = _y + amount;
    _square->setY(_y);
}

//PRIVATE