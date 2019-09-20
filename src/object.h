#ifndef OBJECT_H_
#define OBJECT_H_
#include "iostream"
#include <SDL2/SDL.h>


class Object {
public:
    
    Object(const std::string &image_path, int x, int y, SDL_Renderer* render, int wide, int heigth);
    ~Object();
    void move();
    void updateImage();
    bool moverse = true; //bool para saber si debe moverse el objeto
    int GetPosY();
private:
    
    int _y, _wide;
    float _x, mov_fondo = 9;
    SDL_Surface* _image; 
    SDL_Texture* _texture;
    SDL_Rect* _pos = new SDL_Rect; 
    SDL_Rect* _rect = new SDL_Rect;
    SDL_Renderer* _render = nullptr;
};

#endif