#include <iostream>
#include <SDL2/SDL_image.h>
#include "barrel.h"

//CONSTRUCTOR & DESTRUCTOR
Barrel::Barrel(SDL_Renderer* renderer, float x, float y){
   _renderer = renderer;
   _entity = new Entity(_renderer, WIDTH, HEIGHT, x, y);
}

Barrel::~Barrel(){
    delete(_entity);
}

//PUBLIC
void Barrel::applyHorizontalLeftShift(){
    _entity->applyHorizontalLeftShift();
}

void Barrel::applyHorizontalRighShift(){
    _entity->applyHorizontalRighShift();
}

void Barrel::setSpeed(float speed){
    _entity->setSpeed(speed);
}

void Barrel::updateImage(){
    _entity->updateImage();
}