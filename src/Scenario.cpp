#include "Scenario.h"
#include "iostream"
#include <SDL2/SDL2/SDL_image.h>


void Scenario::move(){
    std::cerr<<"1"<<std::endl;
    int t =  _image->clip_rect.w - _rect->x ;
    if (t > _rect->w ){//-->Cortar al final del background
        std::cerr<<"2"<<std::endl;
        _x = _x + mov_fondo;
        }
    else
    {
        if (cont != 6)
        {
            std::cerr<<"3"<<std::endl;
            nextBackground(path1[cont].c_str());
            cont ++;
            _x = 0;
        }
    }
    _rect->x= _x;
}

void Scenario::updateImage(){
    _texture = SDL_CreateTextureFromSurface( _render, _image ); 
    SDL_RenderCopy( _render, _texture, _rect, _pos );
    SDL_DestroyTexture(_texture);
}

void Scenario::nextBackground(const std::string &image_path){
  //  SDL_FreeSurface(_image);
    if ((_image = IMG_Load(image_path.c_str()))==NULL){
        std::cerr <<  "No pudo cargar imagen fondo.\n";
        std::cerr << "Se carga imagen por default imagen verde\n";
        _image = SDL_CreateRGBSurface(0, _w_window, _h, 32, 0, 0, 0, 0);
        SDL_Rect d;
        d.y = 0;
        d.x=0;
        d.h=_h/2;
        d.w=_w_window;
        //Mitad superior transparente
        SDL_FillRect(_image,&d , SDL_MapRGB(_image->format, 0, 255, 0));
       // cont=6;
    }
    SDL_SetColorKey(_image, SDL_TRUE,
    SDL_MapRGB(_image->format, 0, 162, 232));
}

