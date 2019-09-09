#include "square.h"
#include "window.h"
#include <iostream>

//CONSTRUCTOR & DESTRUCTOR
Square::Square(int side, int x, int y, int r, int g, int b, int a):
_side(side), _x(x), _y(y), _r(r), _g(g), _b(b), _a(a){
}

Square::Square(int side, int x, int y, std::string &image_path):
_side(side), _x(x), _y(y){

    auto surface = IMG_Load(image_path.c_str());
    if (!surface){
        raiseException("failed to create surface");
    }

    _texture = SDL_CreateTextureFromSurface(Window::_renderer,surface);
    if (!_texture){
        raiseException("failed to create texture");
    }
    SDL_FreeSurface(surface);
}

Square::~Square(){
    SDL_DestroyTexture(_texture);
}

//PUBLIC
void Square::display(){
    _rectangle = {_x, _y,_side, _side};
    SDL_RenderCopy(Window::_renderer,_texture,nullptr,&_rectangle);
    /*
    if (_texture){
        SDL_RenderCopy(Window::_renderer,_texture,nullptr,&_rectangle);
    }
    else{
        SDL_SetRenderDrawColor(Window::_renderer, _r, _g, _b, _a); //HARDCODEADO
        SDL_RenderFillRect(Window::_renderer,&_rectangle);
    }*/
}

void Square::pollEvents(SDL_Event &event){ //HARDCODEADO
    if (event.type == SDL_KEYDOWN){
        switch (event.key.keysym.sym){
        case SDLK_LEFT:
            _x -= 10;
            break;
        case SDLK_RIGHT:
            _x += 10;
            break;
        case SDLK_UP:
            _y -= 10;
            break;
        case SDLK_DOWN:
            _y += 10;
            break;
        }
    }
}

//PRIVATE

void Square::raiseException(std::string mesage){
    std::cout<<mesage + "\n";
}