#include "far_background.h"
#include "iostream"
#include <SDL2/SDL_image.h>

Far_background::Far_background( const std::string &image_path, int h,int w):
    _h(h*h/w),_x(0) {
    _image =IMG_Load(image_path.c_str());    
    _pos->x=0;
    _pos->y= 0;
    _pos->h= _h;
    _w=_h*(_image->clip_rect.w)/(_image->clip_rect.h);
    std::cerr << _w;
    std::cerr <<"heigth: "<<_w<<"\n"<<"width: "<<_h<<"\n"<<std::endl;

     //Transparencia en el contorno celeste del suelo
        SDL_SetColorKey(_image, SDL_TRUE,
        SDL_MapRGB(_image->format, 0, 162, 232));
}

void Far_background::move(){
    _x = _x - 0.5;

}

void Far_background::updateImage(SDL_Window* window){
    _pos->x = _x;
    _pos->w = _w;
    SDL_Surface* test;
    SDL_BlitScaled(_image,&(_image->clip_rect),test,_pos);

    std::cerr <<"heigth test: "<<test->clip_rect.h<<"\n"<<"width: "<<test->clip_rect.w<<"\n"<<std::endl;
    SDL_Surface* ScreenSurface = SDL_GetWindowSurface(window);
    SDL_BlitScaled(_image,NULL, ScreenSurface,_pos);
    SDL_FreeSurface(ScreenSurface);
}