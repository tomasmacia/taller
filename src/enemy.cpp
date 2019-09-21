#include "enemy.h"
#include "iostream"
#include <SDL2/SDL_image.h>

//CONSTRUCTOR && DESTRUCTOR
Enemy::Enemy(const std::string &image_path, int x, int y, SDL_Renderer* render, int wide, int heigth):
    _x(x), _y(y),_render(render),_wide(wide) {
    if ((_image = IMG_Load(image_path.c_str()))==NULL){
        /* Carga la imagen o carga pantallitas azules donde deberian estar los objetos */
        std::cerr <<  "No pudo cargar imagen.\n";
        std::cerr << "Se carga imagen por default\n";
        _image = SDL_CreateRGBSurface(0, 56, 125, 32, 0, 0, 0, 0);
        SDL_FillRect(_image, NULL, SDL_MapRGB(_image->format, 0, 0, 255));
            } 
    _pos->x= x;
    _pos->y= y;//2000 a 120 --> posiciones que aparentan estar en el suelo
    _pos->h=(heigth) *0.66;// _image->clip_rect.h*2.8;
    _pos->w= (heigth) * .3; // _image->clip_rect.w*2.8; 
    _rect->w=_image->clip_rect.w/cant_img_sprite;
    _rect->h=_image->clip_rect.h;
    _rect->x = _image->clip_rect.w/cant_img_sprite * spriteToload;
    _rect->y=0;
    //para donde camina
    if ((int)x%3 !=0){flip =SDL_FLIP_HORIZONTAL;mov_default*=(-1);}

    
    
     //Transparencia en el contorno celeste del suelo
        SDL_SetColorKey(_image, SDL_TRUE,
        SDL_MapRGB(_image->format, 88, 184, 248));

}

//PUBLIC
void Enemy::move(){
    if(moverse){
        _x = _x - mov_fondo;
        _pos->x = _x;
    }
}

int Enemy::GetPosY(){
    return _y;
}

void Enemy::updateImage(){

    _x = _x + mov_default;
    _pos->x =_x;
    cont++;

    //Solo se renderiza lo qeu esta cerca de la pantalla
    if (_pos->x>-200 &_pos->x < _wide/*wide windows*/){
    //si quiero realizar una accion
        
        //aumento el contador de acciones
        if(cont >= loop){
        //si el contador es igual al numero que creo es
        //vuelvo el contador a 0 y cambio de sprite en
        //la secuencia
            cont = 0;
            spriteToload++;
            if (spriteToload ==cant_img_sprite-1){
                //si llegue al final de la secuencia, mi estado es quieto
                // y estado previo es "accion," al cargar la imagen defaullt lo hago.
                spriteToload= 0;
                cont = 0;
            }
        }

    _rect->x = _image->clip_rect.w/cant_img_sprite * spriteToload;
    _texture = SDL_CreateTextureFromSurface( _render, _image );
    SDL_RenderCopyEx( _render, _texture, _rect, _pos ,0,NULL,flip);

    
    SDL_DestroyTexture(_texture);
    
}
}
  /*      _texture = SDL_CreateTextureFromSurface( _render, _image ); 
        SDL_RenderCopy( _render, _texture, _rect, _pos );
        SDL_DestroyTexture(_texture);
    }
    
}*/

//PRIVATE