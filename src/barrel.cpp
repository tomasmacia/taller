#include <iostream>
#include <SDL2/SDL_image.h>
#include "barrel.h"

//CONSTRUCTOR & DESTRUCTOR
Barrel::Barrel(SDL_Renderer* renderer, float x, float y, float minScaleFactor, float maxY, float minY,
                bool perspectiveSensitive){
   Sprite* sprite = new Sprite(IMAGE_PATH,R_TRANSAPRENT,G_TRANSAPRENT,B_TRANSAPRENT);
   _entity = new Entity(renderer, MAX_WIDTH, MAX_HEIGHT, x, y, sprite, minScaleFactor, maxY, minY,
                        perspectiveSensitive);
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

float Barrel::getY(){
    return _entity->getY();
}

void Barrel::updateImage(){
    _entity->updateImage();
}