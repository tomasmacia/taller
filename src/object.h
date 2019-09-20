#ifndef OBJECT_H_
#define OBJECT_H_
#include "iostream"
#include <SDL2/SDL.h>

class Object {

private:


    float _y;
    float _x, mov_fondo = 12;

    SDL_Surface* _image; 
    SDL_Texture* _texture;
    SDL_Rect* _pos = new SDL_Rect; 
    SDL_Rect* _rect = new SDL_Rect;
    SDL_Renderer* _render = nullptr;

public:
    bool moverse = true; //bool para aber si debe moverse el objeto
    
    Object(const std::string &image_path, int x, int y, SDL_Renderer* render);
    ~Object();

    void move();
    void updateImage();
};

#endif