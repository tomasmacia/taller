#include "background.h"
#include "iostream"
#include <SDL2/SDL_image.h>

Background::Background( const std::string &image_path, int h):
    _h(h),_x(0) {
    _image =IMG_Load(image_path.c_str());
    _w=(_image->clip_rect.w)*(_h/_image->clip_rect.h);
    _pos->x=0;
    _pos->y= 0;
    _pos->h= h;
     //Transparencia en el contorno celeste del suelo
        SDL_SetColorKey(_image, SDL_TRUE,
        SDL_MapRGB(_image->format, 0, 162, 232));
}

void Background::move(){
    _x = _x- 14;
    std::cerr <<"pos: "<< _pos->x <<"  "<<"guardado: "<<_x<<std::endl;
    
}

void Background::updateImage(SDL_Window* window){
    _pos->x=_x;
    _pos->w=_w;
    SDL_Surface* ScreenSurface = SDL_GetWindowSurface(window);
    SDL_BlitScaled(_image,NULL, ScreenSurface,_pos);
    SDL_FreeSurface(ScreenSurface);
}
