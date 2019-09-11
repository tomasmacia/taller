#ifndef BACKROUND_H_
#define BACKROUND_H_
#include "iostream"
#include <SDL2/SDL.h>

class Background {
public:
    
    Background(const std::string &image_path, int h);
    void move();
    void updateImage(SDL_Window* window);
private:
    int _x,_w, _h; 
    SDL_Surface* _image; 
    SDL_Rect* _pos = new SDL_Rect;  
};

#endif