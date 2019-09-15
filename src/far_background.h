#ifndef FAR_BACKGROUND_H_
#define FAR_BACKGROUND_H_
#include "string"
#include <SDL2/SDL.h>

class Far_background {
public:
    
    Far_background(const std::string &image_path, int h,int w, SDL_Renderer* render);
    ~Far_background();
    void move();
    void updateImage();
private:
    int _w, _h,_w_window,cont = 5; //-->cont es temporal
    float _x; //--> posicionde la imagen
    SDL_Surface* _image; 
    SDL_Texture* _texture;
    SDL_Rect* _pos = new SDL_Rect;
    SDL_Rect* _rect = new SDL_Rect;
    SDL_Renderer* _render = nullptr;
    void nextBackground(const std::string &image_path);//
};

#endif