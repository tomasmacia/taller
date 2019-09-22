#ifndef BARREL_H_
#define BARREL_H_

#include <iostream>
#include <SDL2/SDL.h>
#include <string>
#include "entity.h"

class Barrel{       //IMPLEMENTA PARTE DE LA INTERFAZ DE ENTITY

private:

    Entity* _entity;

    const float MAX_WIDTH = 185;
    const float MAX_HEIGHT = 250;

    const std::string IMAGE_PATH = "Sprites/barril.png";
    const int R_TRANSAPRENT = 88;
    const int G_TRANSAPRENT = 184;
    const int B_TRANSAPRENT = 248;

public:    
    Barrel(SDL_Renderer* renderer, float x, float y, float minScaleFactor, float maxY, float minY, bool perspectiveSensitive);
    ~Barrel();

    void applyHorizontalLeftShift();
    void applyHorizontalRighShift();
    void setSpeed(float speed);

    float getY();
    
    void updateImage();
};
#endif