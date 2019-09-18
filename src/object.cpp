#include "object.h"
#include "iostream"
#include <SDL2/SDL_image.h>

Object::Object(const std::string &image_path, int x,int y, SDL_Renderer* render):
    _x(x), _y(y),_render(render) {
    _image =IMG_Load(image_path.c_str());  
    _pos->x= x;
    _pos->y= y;//350 a 245 --> posiciones que aparentan estar en el suelo
    _pos->h= _image->clip_rect.h*2.8;
    _pos->w= _image->clip_rect.w*2.8; 
    _rect->h = _image->clip_rect.h;
    _rect->w = _image->clip_rect.w;
    _rect->x = 0;
    _rect->y = 0;
     //Transparencia en el contorno celeste del suelo
        SDL_SetColorKey(_image, SDL_TRUE,
        SDL_MapRGB(_image->format, 88, 184, 248));  
}

void Object::move(){
    if(moverse){
        _pos->x = _pos->x - mov_fondo;
    //    std::cerr << "----------------"<<std::endl;
     //   std::cerr <<"POSICIO X DE BARRIL: "<< _pos->x << std::endl;
    }
}

void Object::updateImage(){
    _texture = SDL_CreateTextureFromSurface( _render, _image ); 
    SDL_RenderCopy( _render, _texture, _rect, _pos );
    SDL_DestroyTexture(_texture);
    
}


Object::~Object(){
    SDL_DestroyTexture(_texture);
}
