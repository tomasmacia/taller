#include "object.h"
#include "iostream"
#include <SDL2/SDL_image.h>

Object::Object(const std::string &image_path, int x,int y, SDL_Renderer* render, int wide,int heigth):
    _x(x), _y(y),_render(render),_wide(wide) {
    if ((_image = IMG_Load(image_path.c_str()))==NULL){
        /* Carga la imagen o carga pantallitas azules donde deberian estar los objetos */
        std::cerr <<  "No pudo cargar imagen.\n";
        std::cerr << "Se carga imagen por default\n";
        _image = SDL_CreateRGBSurface(0, 56, 125, 32, 0, 0, 0, 0);
        SDL_FillRect(_image, NULL, SDL_MapRGB(_image->format, 0, 0, 255));
            } 
    _pos->x= x;
    _pos->y= y;//200 a 120 --> posiciones que aparentan estar en el suelo
    _pos->h=(heigth) *0.66;// _image->clip_rect.h*2.8;
    _pos->w= (heigth) * .3; // _image->clip_rect.w*2.8; 
    _rect->h = _image->clip_rect.h;
  //  _rect->w = _image->clip_rect.w;
    _rect->x = 0;
    _rect->y = 0;
     //Transparencia en el contorno celeste del suelo
        SDL_SetColorKey(_image, SDL_TRUE,
        SDL_MapRGB(_image->format, 88, 184, 248));  
}

void Object::move(){
    if(moverse){
        _x = _x - mov_fondo;
        _pos->x = _x;
    }
}

void Object::updateImage(){
    
}


Object::~Object(){
    SDL_DestroyTexture(_texture);
}

int Object::GetPosY(){
    return _y;
}
