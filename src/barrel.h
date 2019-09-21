#ifndef OBJECT_H_
#define OBJECT_H_
#include <iostream>
#include <SDL2/SDL.h>
#include <string>
#include "entity.h"

class Barrel{       //IMPLEMENTA PARTE DE LA INTERFAZ DE ENTITY

private:

   Entity* _entity;

   float WIDTH = 40;
   float HEIGHT = 80;
   const std::string &IMAGE_PATH = "Sprites/barril.png";

   SDL_Renderer* _renderer;

public:    
    Barrel(SDL_Renderer* renderer, float x, float y);
    ~Barrel();

    void applyHorizontalLeftShift();
    void applyHorizontalRighShift();
    void setSpeed(float speed);
    
    void updateImage();
};
#endif