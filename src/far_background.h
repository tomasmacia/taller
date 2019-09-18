#ifndef FAR_BACKGROUND_H_
#define FAR_BACKGROUND_H_
#include "string"
#include <SDL2/SDL.h>
#include <vector>
using namespace std;

class Far_background {
public:
    
    Far_background(vector<string> path, int h,int w, SDL_Renderer* render, float mov_fondo);
    ~Far_background();
    void move();
    void updateImage();

private:
    vector<string> path1;
    float mov_fondo ;
    int _w, _h,_w_window,cont = 1; //-->cont cambio de imagenes
    float _x; //--> posicionde la imagen
    SDL_Surface* _image; 
    SDL_Texture* _texture;
    SDL_Rect* _pos = new SDL_Rect;
    SDL_Rect* _rect = new SDL_Rect;
    SDL_Renderer* _render = nullptr;
    void nextBackground(const std::string &image_path);//
};

#endif