#include "far_background.h"
#include "iostream"
#include <SDL2/SDL_image.h>

Far_background::Far_background( const std::string &image_path, int h,int w, SDL_Renderer* render):
    _h(h*.8125),_x(0),_w_window(w),_render(render) {
    _image =IMG_Load(image_path.c_str());  
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
        _x = _x + 0.3/*1.4*/;
        }
    else
    {
        if (cont == 5)
        {
            nextBackground("Sprites/FF_Stage4_back2.png");
            cont --;
            _x = 0;
        }
        else if (cont == 4)
        {
            nextBackground("Sprites/FF_Stage4_back3.png");
            cont --;
            _x = 0;
        }
        else if(cont == 3)
        {
            nextBackground("Sprites/FF_Stage4_back4.png");
            cont --;
            _x = 0;
        }
        else if (cont == 2)
        {
            nextBackground("Sprites/FF_Stage4_back5.png");            
            cont--;
            _x = 0;
        }
        else if (cont == 1)
        {
            nextBackground("Sprites/FF_Stage4_back6.png");
            cont --;
            _x = 0;
        } 
    }
    _rect->x= _x;
}

void Far_background::updateImage(SDL_Window* window){
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
