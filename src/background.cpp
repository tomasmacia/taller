#include "background.h"
#include "iostream"
#include <SDL2/SDL_image.h>

Background::Background( const std::string &image_path, int h,int w):
    _h(h),_x(0), _w_window(w) {
    _image =IMG_Load(image_path.c_str());
    _w=h*((_image->clip_rect.w)/(_image->clip_rect.h));
    _pos->x=0;
    _pos->y= 0;
    _pos->h= h;
     //Transparencia en el contorno celeste del suelo
    SDL_SetColorKey(_image, SDL_TRUE,
    SDL_MapRGB(_image->format, 0, 162, 232));
}

void Background::move(){
    int t =  _x +_w ;                        
    //  cosas para cambiar 
    //de background, si la imagen es muy
    // grande, el largo width es gigante(20000+ pixel)
    // por lo que la reescala es tardia.
    // Idea de cortar el mapa en pedazos y 
    // cargarlos en el momento justo, asi la reescala
    //es menor (20000 vs 8000 o 6000)

    if (t> _w_window ){//-->Cortar al final del background
        _x = _x-7;}    //cant de pixeles movida
    else
    {
        if (cont == 5)
        {
            nextBackground("Sprites/FF_Stage4_floor2.png");
            cont --;
            _x = 0;
        }
        else if (cont == 4)
        {
            nextBackground("Sprites/FF_Stage4_floor3.png");
            cont --;
            _x = 0;
        }
        else if(cont == 3)
        {
            nextBackground("Sprites/FF_Stage4_floor4.png");
            cont --;
            _x=0;
        }
        else if (cont == 2)
        {
            nextBackground("Sprites/FF_Stage4_floor5.png");            
            cont--;
            _x = 0;
        }
        else if (cont == 1)
        {
            nextBackground("Sprites/FF_Stage4_floor6.png");
            cont --;
            _x = 0;
        } 
    }
    
}

void Background::updateImage(SDL_Window* window){
    _pos->x=_x;
    _pos->w=_w; 
   // std::cerr << _h << " - " << _w<< std::endl;
    SDL_Surface* ScreenSurface = SDL_GetWindowSurface(window);
    SDL_BlitScaled(_image,NULL, ScreenSurface,_pos);
    SDL_FreeSurface(ScreenSurface);
}

void Background::nextBackground(const std::string &image_path){
    _image = IMG_Load(image_path.c_str());
    _w=_h*(_image->clip_rect.w)/(_image->clip_rect.h);
    SDL_SetColorKey(_image, SDL_TRUE,
    SDL_MapRGB(_image->format, 0, 162, 232));
  //  std::cerr << _h << " - " << _w<< std::endl;
}
