#ifndef BACKGROUND_H_
#define BACKGROUND_H_

#include "iostream"
#include <SDL2/SDL.h>


class Background {
public:
    
    Background(const std::string &image_path, int h, int w, SDL_Renderer* render,class Game* owner);
    ~Background();
    void move();
    void updateImage();
private:
    int _w, _h,_w_window,cont=5; 
    float _x;
  class Game* _owner = nullptr;
    SDL_Surface* _image; 
    SDL_Texture* _texture;
    SDL_Rect* _pos = new SDL_Rect; 
    SDL_Rect* _rect = new SDL_Rect;
    SDL_Renderer* _render = nullptr;
    void nextBackground(const std::string &image_path);//
};

#endif