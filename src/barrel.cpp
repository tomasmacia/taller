#include <iostream>
#include <SDL2/SDL_image.h>
#include "barrel.h"

//CONSTRUCTOR & DESTRUCTOR
Barrel::Barrel(SDL_Renderer* renderer, float x, float y){
   _renderer = renderer;
   Sprite* sprite = new Sprite(IMAGE_PATH,R_TRANSAPRENT,G_TRANSAPRENT,B_TRANSAPRENT);
   _entity = new Entity(_renderer, WIDTH, HEIGHT, x, y, sprite);
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