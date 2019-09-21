#include <iostream>
#include <SDL2/SDL_image.h>
#include "barrel.h"

//CONSTRUCTOR & DESTRUCTOR
Barrel::Barrel(SDL_Renderer* renderer, float x, float y, float minScaleFactor, float maxY, float minY){
   _renderer = renderer;
   Sprite* sprite = new Sprite(IMAGE_PATH,R_TRANSAPRENT,G_TRANSAPRENT,B_TRANSAPRENT);
   _entity = new Entity(_renderer, DEFAULT_WIDTH, DEFAULT_HEIGHT, x, y, sprite, minScaleFactor, maxY, minY);


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