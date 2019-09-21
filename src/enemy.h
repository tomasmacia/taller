#ifndef ENEMY_H_
#define ENEMY_H_

#include "iostream"
#include <SDL2/SDL.h>

class Enemy{

public:
    Enemy(const std::string &image_path, int x, int y, SDL_Renderer* render, int wide, int heigth);
    int GetPosY();
    void updateImage();
    void move();

    bool moverse = true;



private:
    int _y, _wide;
    float _x, mov_fondo = 2.2;
    SDL_Surface* _image; 
    SDL_Texture* _texture;
    SDL_Rect* _pos = new SDL_Rect; 
    SDL_Rect* _rect = new SDL_Rect;
    SDL_Renderer* _render = nullptr;
};
#endif