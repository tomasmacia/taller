#ifndef BACKGROUND_H_
#define BACKGROUND_H_
#include "iostream"
#include <SDL2/SDL.h>
#include<vector>
using namespace std;

class Background {
public:
    
    Background(vector<string> g, int h, int w, SDL_Renderer* render,class Game* owner, float mov_fondo, int lvl);
    ~Background();
    void move();
    void updateImage();

private:
    int lvl_parallax;
    vector<string> g1;
    int _w, _h,_w_window,cont=0; //contador de cambio de imagen
    float _x;
    float mov_fondo = 3 ;
  class Game* _owner = nullptr;
    SDL_Surface* _image = NULL; 
    SDL_Texture* _texture;
    SDL_Rect* _pos = new SDL_Rect; 
    SDL_Rect* _rect = new SDL_Rect;
    SDL_Renderer* _render = nullptr;
    void nextBackground(const std::string &image_path);
};

#endif