#include "far_background.h"
#include "iostream"
#include <SDL2/SDL_image.h>

Far_background::Far_background( const std::string &image_path, int h,int w):
    _h(h*.8125),_x(0),_w_window(w) {
    _image =IMG_Load(image_path.c_str());    
    _pos->x=0;
    _pos->y= 0;
    _pos->h= _h;
    _w=_h*(_image->clip_rect.w)/(_image->clip_rect.h);
    //std::cerr << _h << " - " << _w<< std::endl;
     //Transparencia en el contorno celeste del suelo
        SDL_SetColorKey(_image, SDL_TRUE,
        SDL_MapRGB(_image->format, 0, 162, 232));
}

void Far_background::move(){
    if (_x +_w > _w_window ){//-->Cortar al final del background
        _x = _x - 1.4;
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
            _x=0;
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
    
}

void Far_background::updateImage(SDL_Window* window){
    _pos->x=_x;
    _pos->w=_w; 
   // std::cerr << _h << " - " << _w<< std::endl;
    SDL_Surface* ScreenSurface = SDL_GetWindowSurface(window);
    SDL_BlitScaled(_image,NULL, ScreenSurface,_pos);
    SDL_FreeSurface(ScreenSurface);
}

void Far_background::nextBackground(const std::string &image_path){
    _image = IMG_Load(image_path.c_str());
    _w=_h*(_image->clip_rect.w)/(_image->clip_rect.h);
    SDL_SetColorKey(_image, SDL_TRUE,
    SDL_MapRGB(_image->format, 0, 162, 232));
  //  std::cerr << _h << " - " << _w<< std::endl;
}



    /*
    {
        if (cont == 0)
        {
            cargo1();
            cont =1;
            _x = 0;
        }
        else if (cont == 1)
        {
            cargo2();
            cont = 2;
            _x = 0;
        }
        else if(cont == 2)
        {
            cargo3();
            cont =-1;
            _x=0;
        }
    }
    }

void Far_background::updateImage(SDL_Window* window){
    _pos->x = _x;
    _pos->w = _w;
   // std::cerr << _x << " - " << -(_w - _w_window) << std::endl;
    SDL_Surface* ScreenSurface = SDL_GetWindowSurface(window);
    SDL_BlitScaled(_image,NULL, ScreenSurface,_pos);
    SDL_FreeSurface(ScreenSurface);
}

void Far_background::cargo1(){
    _image = IMG_Load("Sprites/FF_Stage4_back1.png");
    _w=_h*(_image->clip_rect.w)/(_image->clip_rect.h);
 //   std::cerr << _h << " - " << _w<< std::endl;
}

void Far_background::cargo2(){
    _image = IMG_Load("Sprites/FF_Stage4_back2.png");
    _w=_h*(_image->clip_rect.w)/(_image->clip_rect.h);
   // std::cerr << _h << " - " << _w<< std::endl;
}

void Far_background::cargo3(){
    _image = IMG_Load("Sprites/FF_Stage4_back3.png");
    _w=_h*(_image->clip_rect.w)/(_image->clip_rect.h);
    //std::cerr << _h << " - " << _w<< std::endl;*/
