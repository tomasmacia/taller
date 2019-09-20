#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "square.h"

//CONSTRUCTOR & DESTRUCTOR
Square::Square(SDL_Renderer* renderer, float side, float x, float y, int r, int g, int b, int a):
_renderer(renderer), _r(r), _g(g), _b(b), _a(a){
    _rectangle = {x, y, side, side};
    _texture = nullptr;
}

Square::Square(SDL_Renderer* renderer, float side, float x, float y, std::string &image_path):
_renderer(renderer){

    _rectangle = {x, y, side, side};

    auto surface = IMG_Load(image_path.c_str());
    if (!surface){
        raiseException("failed to create surface");
    }

    _texture = SDL_CreateTextureFromSurface(renderer,surface);
    if (!_texture){
        raiseException("failed to create texture");
    }
    SDL_FreeSurface(surface);
}

Square::Square(SDL_Renderer* renderer, float side, float x, float y, SDL_Texture* texture){

    _rectangle = {x, y, side, side};
    _texture = texture;
}

Square::~Square(){
    SDL_DestroyTexture(_texture);
    _texture = nullptr;
    _renderer = nullptr;
}

//PUBLIC
void Square::display(){

    if (_texture){//CON IMAGEN
        SDL_RenderCopy( _renderer, _texture, NULL,&_rectangle );
    }
    else{//SIN IMAGEN CON EL COLOR SETEADO
        SDL_SetRenderDrawColor( _renderer, _r, _g, _b, _a );		
        SDL_RenderFillRect( _renderer, &_rectangle );
    }
}

void Square::setX(float x){
    _rectangle.x = x;
}

void Square::setY(float y){
    _rectangle.y = y;
}

//PRIVATE

void Square::raiseException(std::string mesage){
    std::cout<<mesage + "\n";
}