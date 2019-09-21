#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "appearance.h"

//CONSTRUCTOR & DESTRUCTOR
Appearance::Appearance(SDL_Renderer* renderer, float width, float height, float x, float y, int r, int g, int b, int a):
_r(r), _g(g), _b(b), _a(a){
    _renderer = renderer;
    _rectangle = {x, y, width, height};
}

Appearance::Appearance(SDL_Renderer* renderer, float width, float height, float x, float y, Sprite* sprite){
    _renderer = renderer;
    _rectangle = {x, y, width, height};
    loadImage(sprite);
}

Appearance::Appearance(SDL_Renderer* renderer, float width, float height, float x, float y, SDL_Texture* texture){
    _renderer = renderer;
    _rectangle = {x, y, width, height};
    _texture = texture;
}

Appearance::~Appearance(){
    SDL_DestroyTexture(_texture);
    _texture = nullptr;
    _renderer = nullptr;
}

//PUBLIC
void Appearance::loadImage(Sprite* sprite){

    std::string imagePath = sprite->getImagePath();
    int _r_transparent = sprite->getRTransparent();
    int _g_transparent = sprite->getGTransparent();
    int _b_transparent = sprite->getBTransparent();

    auto surface = IMG_Load(imagePath.c_str());
    if (!surface){
        raiseException("failed to create surface");
    }
    SDL_SetColorKey( surface, SDL_TRUE, SDL_MapRGB( surface->format, _r_transparent, _g_transparent, _b_transparent) );

    if (_texture){
        SDL_DestroyTexture(_texture);
    }

    _texture = SDL_CreateTextureFromSurface(_renderer,surface);
    if (!_texture){
        raiseException("failed to create texture");
    }
    SDL_FreeSurface(surface);
}

void Appearance::updateImage(){

    if (_texture){//CON IMAGEN
        SDL_RenderCopy( _renderer, _texture, NULL,&_rectangle );
    }
    else{//SIN IMAGEN CON EL COLOR SETEADO
        SDL_SetRenderDrawColor( _renderer, _r, _g, _b, _a );		
        SDL_RenderFillRect( _renderer, &_rectangle );
    }
}

void Appearance::setX(float x){
    _rectangle.x = x;
}

void Appearance::setY(float y){
    _rectangle.y = y;
}

void Appearance::setWidth(float width){
    _rectangle.w = width;
}

void Appearance::setHeight(float height){
    _rectangle.h = height;
}

float Appearance::getWidth(){
    return _rectangle.w;
}

float Appearance::getHeigth(){
    return _rectangle.h;
}

//PRIVATE

void Appearance::raiseException(std::string mesage){
    std::cout<<mesage + "\n";
}