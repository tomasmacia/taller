#ifndef CHARACTER_H_
#define CHARACTER_H_
#include "iostream"
#include <SDL2/SDL.h>

class Character {
public:
    Character(const std::string &image_path, int w, int h);
    bool move(bool movLft,bool movRgth, bool movUp, bool movDwn);
    const SDL_Rect getPosition();
    void updateImage(SDL_Window* window);
    void sprite_walk();
private:
    int  _x,_y,_w,_h,_w_window,_h_window, cont=-1;
    SDL_Surface* _image; 
    SDL_Rect* _pos = new SDL_Rect; 
};
 
#endif