#ifndef FAR_BACKGROUND_H_
#define FAR_BACKGROUND_H_


#include "string"
#include <SDL2/SDL.h>

class Far_background {
public:
    
    Far_background(const std::string &image_path, int h,int w);
    void move();
    void updateImage(SDL_Window* window);
private:
    int _w, _h; 
    float _x;
    SDL_Surface* _image; 
    SDL_Rect* _pos = new SDL_Rect;  
};

#endif