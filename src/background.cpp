#include "background.h"
#include "iostream"
#include <SDL2/SDL_image.h>
#include"game.h"


Background::Background( const std::string &image_path, int h,int w, SDL_Renderer* render, Game* owner):
    _h(h),_x(0), _w_window(w),_render(render),_owner(owner) {
    _image =IMG_Load(image_path.c_str());
    _w=(w*(_image->clip_rect.h))/h;
    _pos->x=0;           // _pos me indica en que parte de la ventana quiero colocar la imagen   
    _pos->y= 0;          //  (cortada via eleccion de rect). En este caso quiero colocarla en 
    _pos->h= h;          //  pantalla completa, por los que largo y ancho son los mismos
    _pos->w=_w_window;   //  que los de la ventana.
    _rect->h = _image->clip_rect.h;//   Este rect me indica que parte de la imagen 
    _rect->w = _w;                  //   quiero cortar. X e Y siempre son 0,0.
    _rect->x = 0;                   //  El largo, es uno calulado(relacion entre largo y alto mostrado)
    _rect->y = 0;                   //  Y lo alto es directamente la misma que la imagen.
                                    
                                    // Lo mismo se aplica al far_background (tanto rect como pos)

     //Transparencia en el contorno celeste del suelo
    SDL_SetColorKey(_image, SDL_TRUE,
    SDL_MapRGB(_image->format, 0, 162, 232));

}

void Background::move(){
    int t = /*_x+_w*/ _image->clip_rect.w - _rect->x ;
    if (t> _rect->w/*_w_window */){//-->Cortar al final del background el movimiento
        _x = _x+4/*10*/;}    //cant de pixeles movida

    // Idea de cortar el mapa en pedazos y 
    // cargarlos en el momento justo.
    // Si se opta por cargar la imagen de fondo entera, en el game 
    // se pone el path de esa imagen y se quita estos elses
    // Con far_backgrund es distinto, las imagenes de fondo eran 4
    // (1 de noche y 3 de amanecer). Yo lo agrande a 6 para que 
    // tenga misma cantidad de opciones que el background.

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
        /* Aviso que se llego al final */
        else if (cont == 0)
        {
            _owner->pj_in_final();
        }
    }
    _rect->x= _x;
}

void Background::updateImage(){
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
