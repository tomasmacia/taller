#ifndef GAME_COMPONENT_H
#define GAME_COMPONENT_H
#include "iostream"
#include <SDL2/SDL.h>
#include "object.h"

class Game_Component: public Object{

public:
    Game_Component(const std::string &image_path, int x, int y, SDL_Renderer* render, int wide, int heigth, bool isGame_Component, int cant_img);    
    void updateImage();
    void SetMovment(int velocity);

private:
    bool _enemy;
    void circular();
    SDL_RendererFlip flip =SDL_FLIP_NONE;
    int cant_img_sprite = 5,spriteToload = 0, cont = 0, loop = 7, mov_default = 8;
    int rute=2500;
};
#endif