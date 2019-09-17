#include "background.h"
#include "iostream"
#include <SDL2/SDL_image.h>
#include"game.h"

/* Recibe vector con  string de imagenes de fondo, render , alto y ancho de resoucion y al juego */
Background::Background( vector <string> g, int h,int w, SDL_Renderer* render, Game* owner):
    _h(h),_x(0), _w_window(w),_render(render),_owner(owner),g1(g) {
    _image =IMG_Load(g1[0].c_str());
    _w=(w*(_image->clip_rect.h))/h;
    _pos->x=0;           // _pos me indica en que parte de la ventana quiero colocar la imagen   
    _pos->y= 0;          //  (cortada via eleccion de rect). En este caso quiero colocarla en 
    _pos->h= h;          //  pantalla completa, por los que largo y ancho son los mismos
    _pos->w=_w_window;   //  que los de la ventana.
    _rect->h = _image->clip_rect.h;//   Este rect me indica que parte de la imagen 
    _rect->w = _w;                  //   quiero cortar. X e Y siempre son 0,0. al ppio.
    _rect->x = _x;                   //  El largo, es uno calulado(relacion entre largo y alto mostrado)
    _rect->y = 0;                   //  Y lo alto es directamente la misma que la imagen.
                                    
                                    // Lo mismo se aplica al far_background (tanto rect como pos)

     //Transparencia en el contorno celeste del suelo
    SDL_SetColorKey(_image, SDL_TRUE,
    SDL_MapRGB(_image->format, 0, 162, 232));
    

}

void Background::move(){
    int t = _image->clip_rect.w - _rect->x ;
    if (t> _rect->w){//-->Cortar al final del background el movimiento
        _x = _x+mov_fondo;}    //cant de pixeles movida

    // Idea de cortar el mapa en pedazos y 
    // cargarlos en el momento justo.
    // Si se opta por cargar la imagen de fondo entera, en el game 
    // se pone el path de esa imagen y se quita estos elses

    //IMAGEN A PEDAZOS PARECE SER MAS EFICIENTE

    // Con far_backgrund es distinto, las imagenes de fondo eran 4
    // (1 de noche y 3 de amanecer). Yo lo agrande a 6 para que 
    // tenga misma cantidad de opciones que el background.
    
    else
    {
        if (cont != 6){
        nextBackground(g1[cont].c_str());
        cont ++;
        _x = 0;
        }
        /* Aviso que se llego al final */
        else 
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
