#ifndef ENEMY_H_
#define ENEMY_H_
#include "iostream"
#include <SDL2/SDL.h>
#include "object.h"

class Enemy: public Object{

public:
    Enemy(const std::string &image_path, int x, int y, SDL_Renderer* render, int wide, int heigth);    
    void updateImage();
    void SetMovment(int velocity);

private:
    void circular();
    SDL_RendererFlip flip =SDL_FLIP_NONE;
    int cant_img_sprite = 5,spriteToload = 0, cont = 0, loop = 7, mov_default = 8;
    int rute=2500;
};
#endif