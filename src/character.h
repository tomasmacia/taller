#ifndef CHARACTER_H_
#define CHARACTER_H_

#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include <string.h>
#include "entity.h"

class Character {

private:
    Entity* _entity = nullptr;

    const float MAX_WIDTH = 250;
    const float MAX_HEIGHT = 600;

    const std::string IMAGE_PATH = "Sprites/cody.png";
    const int R_TRANSAPRENT = 88;
    const int G_TRANSAPRENT = 184;
    const int B_TRANSAPRENT = 248;
    
public:
    Character(SDL_Renderer* renderer, float x, float y, float minScaleFactor, float maxY, float minY);
    ~Character();

    void enableLeftMovement();
    void enableRightMovement();
    void enableDeepIntoScreenMovement();
    void enableCloserToScreenMovement();
    void disableLeftMovement();
    void disableRightMovement();
    void disableDeepIntoScreenMovement();
    void disableCloserToScreenMovement();
    void jump();
    void hit();
    void crouch();

    float getY();
    float getWidth();
    float getHeigth();
     
    void update();
 };
 #endif
    //SDL_RendererFlip flip =SDL_FLIP_NONE;