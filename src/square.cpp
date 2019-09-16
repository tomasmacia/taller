#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "square.h"
#include "window.h"

//CONSTRUCTOR & DESTRUCTOR
Square::Square(SDL_Renderer* renderer, int side, int x, int y, int r, int g, int b, int a):
_renderer(renderer), _side(side), _x(x), _y(y), _r(r), _g(g), _b(b), _a(a){
    _rectangle = {_x, _y,_side, _side};
}

Square::Square(SDL_Renderer* renderer, int side, int x, int y, std::string &image_path):
_renderer(renderer), _side(side), _x(x), _y(y){

    _rectangle = {_x, _y,_side, _side};

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
Square::~Square(){
    SDL_DestroyTexture(_texture);
    _texture = nullptr;
    _renderer = nullptr;
}

//PUBLIC
void Square::display(){

    if (_texture){
        SDL_RenderCopy( _renderer, _texture, NULL, NULL );
    }
    else{
        SDL_SetRenderDrawColor( _renderer, _r, _g, _b, _a );		
        SDL_RenderFillRect( _renderer, &_rectangle );
    }
}

//PRIVATE

void Square::raiseException(std::string mesage){
    std::cout<<mesage + "\n";
}