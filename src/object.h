#ifndef OBJECT_H_
#define OBJECT_H_
#include "iostream"
#include <SDL2/SDL.h>


class Object {
public:
    
    Object(const std::string &image_path, int h, int w, SDL_Renderer* render);
    ~Object();
    void move();
    void updateImage();
private:
    int _w, _h,_w_window; 
    float _x;
    SDL_Surface* _image; 
    SDL_Texture* _texture;
    SDL_Rect* _pos = new SDL_Rect; 
    SDL_Rect* _rect = new SDL_Rect;
    SDL_Renderer* _render = nullptr;
};

#endif