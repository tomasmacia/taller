#include "background.h"
#include "iostream"
#include <SDL2/SDL_image.h>
#include"game.h"

/* Recibe vector con  string de imagenes de fondo, render , alto y ancho de resoucion y al juego */
Background::Background( vector <string> g, int h,int w, SDL_Renderer* render, Game* owner, float mov_fondo, int lvl):
    _h(h),_x(0), _w_window(w),_render(render),_owner(owner),g1(g), mov_fondo(mov_fondo),lvl_parallax(lvl) {
   if (lvl_parallax==3){
       _h = _h*0.8125;
   }
    nextBackground(g1[cont].c_str());
    _w=(w*(_image->clip_rect.h))/_h;
    _pos->x=0;           // _pos me indica en que parte de la ventana quiero colocar la imagen   
    _pos->y= 0;          //  (cortada via eleccion de rect). En este caso quiero colocarla en 
    _pos->h =_h;          //  pantalla completa, por los que largo y ancho son los mismos
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
    
    else
    {
        if (cont < g1.size()){
            SDL_FreeSurface(_image);
            nextBackground(g1[cont].c_str());
            //cont ++;
            _x = 0;
        }
        /* Aviso que se llego al final */
        else 
        {
            if (lvl_parallax == 1){
                _owner->pj_in_final();
            }
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
    /* Carga la imagen o muestra pantallas verde(backs lejanos) o roja(back del piso)
    si no las encuentra. */
    cont++;
    if ((_image = IMG_Load(image_path.c_str()))==NULL){
        LogManager::logError("No se pudo cargar el sprite del fondo");
        LogManager::logDebug("Se carga una imagen por defecto al no encontrar el sprite del fondo.");
        _image = SDL_CreateRGBSurface(0, _w_window, _h, 32, 0, 0, 0, 0);
        SDL_Rect d;
        if (lvl_parallax == 1 or lvl_parallax==4){
        
            d.y = 0;
            d.x=0;
            d.h=_h/2;
            d.w=_w_window;
            //Mitad superior transparente
            SDL_FillRect(_image,&d , SDL_MapRGB(_image->format, 0, 162, 232));
            d.y = _h/2;
            d.x=0;
            d.h=_h/2;
            d.w=_w_window;
            //mitad inferior roja
            SDL_FillRect(_image,&d , SDL_MapRGB(_image->format, 255, 0, 0));
        }
        if (lvl_parallax == 3){
            d.y = 0;
            d.x=0;
            d.h=_h;
            d.w=_w_window;
            //Mitad superior transparente
            SDL_FillRect(_image,&d , SDL_MapRGB(_image->format, 0, 255, 0));
        }
        if (lvl_parallax == 2){
            //Al dope el lvl 2 y 3 son basicamente iguales
        }
        cont =6;
    }

    SDL_SetColorKey(_image, SDL_TRUE,
    SDL_MapRGB(_image->format, 0, 162, 232));

}

Background::~Background(){
    SDL_DestroyTexture(_texture);
}
