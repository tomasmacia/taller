#ifndef CHARACTER_H_
#define CHARACTER_H_

#include <SDL2/SDL.h>

class Character {
public:
    Character( int x, int w, int h);
    bool move(bool movLft,bool movRgth, bool movUp, bool movDwn);
    const SDL_Rect getPosition();
    void updateImage(SDL_Window* window);
private:
    int  _x,_y,_w,_h,_w_window,_h_window;
    SDL_Surface* _image; 
    SDL_Rect* _pos = new SDL_Rect; 
};
 
#endif