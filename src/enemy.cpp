#include "enemy.h"
#include "iostream"
#include <SDL2/SDL_image.h>
#define zigzag = 500

Enemy::Enemy(const std::string &image_path, int x, int y, SDL_Renderer* render, int wide, int heigth):
     Object( image_path,  x,  y, render, wide,  heigth){
    _rect->w = _image->clip_rect.w/cant_img_sprite;
    if ((int)x%2 !=0){flip =SDL_FLIP_HORIZONTAL;mov_default*=(-1);}

}

void Enemy::SetMovment(int velocity){
    mov_default = velocity;
}

void Enemy::updateImage(){

    _x = _x + mov_default;
    _pos->x =_x;
    circular();
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


void Enemy::circular(){
        rute = rute - abs(mov_default);
        if (rute<0){
            mov_default *= (-1);
            rute = 2500;
            if (flip == SDL_FLIP_HORIZONTAL){
                flip = SDL_FLIP_NONE;
            }
            else
            {
                flip =SDL_FLIP_HORIZONTAL;
            }
            
        }
    }
