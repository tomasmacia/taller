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
    int t =  _x +_w ; //largo de la imagen - corrimiento del origen =
                        // cuanta imagen queda por recorrer

 /*   int d =(1002*_w/_image->clip_rect.w);
    std::cerr << _x +_w << " - " << (1002*_w/_image->clip_rect.w)<< std::endl;
    if (t<d){
        if (cont == 0)
        {                                   
            cargo1();                       
            cont =1;                  //  cosas para cambiar 
            _x = 0;                     //de background, si la imagen es muy
        }                              // grande, el largo width es gigante(20000+ pixel)
        else if (cont == 1)            // por lo que la reescala es tardia.
        {                               // Idea de cortar el mapa en pedazos y 
            cargo2();                  // cargarlos en el momento justo, asi la reescala
            cont = 2;                   //es menor (20000 vs 8000 o 6000)
            _x = 0;
        }
        else if(cont == 2)
        {
            cargo3();
            cont =-1;
            _x=0;
        }
    }*/
    if (t> _w_window ){//-->Cortar al final del background
        _x = _x-7;};    //cant de pixeles movida
}

void Background::updateImage(SDL_Window* window){
    _pos->x=_x;
    _pos->w=_w; 
   // std::cerr << _h << " - " << _w<< std::endl;
    SDL_Surface* ScreenSurface = SDL_GetWindowSurface(window);
    SDL_BlitScaled(_image,NULL, ScreenSurface,_pos);
    SDL_FreeSurface(ScreenSurface);
}

void Background::cargo1(){
    _image = IMG_Load("Sprites/FF_Stage4_floor1b.png");
    _w=_h*(_image->clip_rect.w)/(_image->clip_rect.h);
    SDL_SetColorKey(_image, SDL_TRUE,
    SDL_MapRGB(_image->format, 0, 162, 232));
  //  std::cerr << _h << " - " << _w<< std::endl;
}

void Background::cargo2(){
    _image = IMG_Load("Sprites/FF_Stage4_floor1c.png");
    _w=_h*(_image->clip_rect.w)/(_image->clip_rect.h);
        SDL_SetColorKey(_image, SDL_TRUE,
    SDL_MapRGB(_image->format, 0, 162, 232));
   // std::cerr << _h << " - " << _w<< std::endl;
}

void Background::cargo3(){
    _image = IMG_Load("Sprites/FF_Stage4_floor1d.png");
    _w=_h*(_image->clip_rect.w)/(_image->clip_rect.h);
        SDL_SetColorKey(_image, SDL_TRUE,
    SDL_MapRGB(_image->format, 0, 162, 232));
  //  std::cerr << _h << " - " << _w<< std::endl;
}