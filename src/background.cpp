#include "background.h"
#include "iostream"
#include <SDL2/SDL_image.h>

Background::Background( const std::string &image_path, int h,int w, SDL_Renderer* render):
    _h(h),_x(0), _w_window(w),_render(render) {
    _image =IMG_Load(image_path.c_str());
    _w=/*w;*/(4*(_image->clip_rect.h))/3;
    std::cerr << _w << std::endl;
    _pos->x=0;
    _pos->y= 0;
    _pos->h= h;
    _pos->w=_w_window; 
    _rect->h = _image->clip_rect.h;
    _rect->w = _w;
    _rect->x = 0;
    _rect->y = 0;
     //Transparencia en el contorno celeste del suelo
    SDL_SetColorKey(_image, SDL_TRUE,
    SDL_MapRGB(_image->format, 0, 162, 232));

}

void Background::move(){
    int t = /*_x+_w*/ _image->clip_rect.w - _rect->x ;
   // std::cerr << t << std::endl;                        
    //  cosas para cambiar 
    //de background, si la imagen es muy
    // grande, el largo width es gigante(20000+ pixel)
    // diria que la reescala es le toma tiempo.
    // Idea de cortar el mapa en pedazos y 
    // cargarlos en el momento justo, asi la reescala
    //es menor (20000 vs 8000 o 6000)
    std::cerr << t<< std::endl; 
    if (t> _rect->w/*_w_window */){//-->Cortar al final del background
        _x = _x+2.46/*10*/;}    //cant de pixeles movida
    else
    {
        if (cont == 5)
        {
            nextBackground("Sprites/FF_Stage4_floor2.png");
            cont --;
            _x = 0;
            _rect->x = 0;
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
    _rect->x= _x;
    std::cerr <<" h_dst: "<< _pos->h << " - w_dst: " << _pos->w<<" - x: "<<_pos->x << " - y: " << _pos->y<<" - "<< std::endl;
    std::cerr <<" h_or: "<< _rect->h << " - w_or: " << _rect->w<<" - x: "<<_rect->x << " - y: " << _rect->y<<" - "<< std::endl;
    
}

void Background::updateImage(SDL_Window* window){
    _texture = SDL_CreateTextureFromSurface( _render, _image ); 
    SDL_RenderCopy( _render, _texture, _rect, _pos );
    SDL_DestroyTexture(_texture);
}

void Background::nextBackground(const std::string &image_path){
    SDL_FreeSurface(_image);
    _image = IMG_Load(image_path.c_str());
    SDL_SetColorKey(_image, SDL_TRUE,
    SDL_MapRGB(_image->format, 0, 162, 232));

}

Background::~Background(){
    SDL_DestroyTexture(_texture);
}
