#ifndef BACKROUND_H_
#define BACKROUND_H_
#include "iostream"
#include <SDL2/SDL.h>

class Background {
public:
    
    Background(const std::string &image_path, int h, int w);
    void move();
    void updateImage(SDL_Window* window);
private:
    int _w, _h,_w_window,cont=6; 
    float _x;
    SDL_Surface* _image; 
    SDL_Rect* _pos = new SDL_Rect; 
    void cargo1();//
    void cargo2();//-->Estos son para probar cambio de escenario
    void cargo3();//  de atras en un lvl 
};

#endif