#ifndef OBJECT_H_
#define OBJECT_H_
#include <iostream>
#include <SDL2/SDL.h>
#include <string>
#include "entity.h"

class Barrel{       //IMPLEMENTA PARTE DE LA INTERFAZ DE ENTITY

private:

   Entity* _entity;

   float MAX_WIDTH = 450;
   float MAX_HEIGHT = 600;
   
   const std::string IMAGE_PATH = "Sprites/barril.png";
    int R_TRANSAPRENT = 88;
    int G_TRANSAPRENT = 184;
    int B_TRANSAPRENT = 248;

   SDL_Renderer* _renderer;

public:    
    Barrel(SDL_Renderer* renderer, float x, float y, float minScaleFactor, float maxY, float minY);
    ~Barrel();

    void applyHorizontalLeftShift();
    void applyHorizontalRighShift();
    void setSpeed(float speed);

    float getY();
    
    void updateImage();
};
#endif