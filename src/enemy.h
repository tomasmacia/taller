#ifndef ENEMY_H_
#define ENEMY_H_
#include "iostream"
#include <SDL2/SDL.h>

class Enemy{

public:
    Enemy(const std::string &image_path, int x, int y, SDL_Renderer* render, int wide, int heigth);    
    void updateImage();
    void move();
    void SetMovment(int velocity); 
    bool moverse = true;
    int GetPosY();


private:
    SDL_RendererFlip flip =SDL_FLIP_NONE;
    int cant_img_sprite = 5,spriteToload = 0, cont = 0, loop = 7, mov_default = 5;
    int _y, _wide;
    float _x, mov_fondo = 1.57;
    SDL_Surface* _image; 
    SDL_Texture* _texture;
    SDL_Rect* _pos = new SDL_Rect; 
    SDL_Rect* _rect = new SDL_Rect;
    SDL_Renderer* _render = nullptr;
};
#endif