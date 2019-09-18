#include "far_background.h"
#include "iostream"
#include <SDL2/SDL_image.h>

Far_background::Far_background( vector <string> path, int h,int w, SDL_Renderer* render):
    _h(h*.8125),_x(0),_w_window(w),_render(render), path1(path) {
    _image =IMG_Load(path1[0].c_str());  
    _pos->x=0;
    _pos->y= 0;
    _pos->h= _h;
    _pos->w=_w_window; 
    _w= (_w_window*(_image->clip_rect.h))/_h;
    _rect->h = _image->clip_rect.h;
    _rect->w = _w;
    _rect->x = 0;
    _rect->y = 0;
     //Transparencia en el contorno celeste del suelo
        SDL_SetColorKey(_image, SDL_TRUE,
        SDL_MapRGB(_image->format, 0, 162, 232));  
}

void Far_background::move(){
    
    int t =  _image->clip_rect.w - _rect->x ;
    if (t > _rect->w ){//-->Cortar al final del background
        _x = _x + mov_fondo/*1.25*/;
        }
    else
    {
        if (cont != 6)
        {
            nextBackground(path1[cont].c_str());
            cont ++;
            _x = 0;
        }
    }
    _rect->x= _x;
}

void Far_background::updateImage(){
    _texture = SDL_CreateTextureFromSurface( _render, _image ); 
    SDL_RenderCopy( _render, _texture, _rect, _pos );
    SDL_DestroyTexture(_texture);
}

void Far_background::nextBackground(const std::string &image_path){
    SDL_FreeSurface(_image);
    _image = IMG_Load(image_path.c_str());
    SDL_SetColorKey(_image, SDL_TRUE,
    SDL_MapRGB(_image->format, 0, 162, 232));
}

Far_background::~Far_background(){
    SDL_DestroyTexture(_texture);
}
