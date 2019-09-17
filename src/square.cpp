#include "square.h"
#include <iostream>

//CONSTRUCTOR & DESTRUCTOR
Square::Square(int side, int x, int y, int r, int g, int b, int a):
_side(side), _x(x), _y(y), _r(r), _g(g), _b(b), _a(a){

}
//PUBLIC
void Square::display(){

    _rectangle.w = _side;
    _rectangle.h = _side;
    _rectangle.x = _x;
    _rectangle.y = _y;

    SDL_SetRenderDrawColor(Window::_renderer, _r, _g, _b, _a); //HARDCODEADO
    SDL_RenderFillRect(Window::_renderer,&_rectangle);
}

// void Square::pollEvents(SDL_Event &event){ //HARDCODEADO
//     if (event.type == SDL_KEYDOWN){
//         switch (event.key.keysym.sym){
//         case SDLK_LEFT:
//             _x -= 10;
//             break;
//         case SDLK_RIGHT:
//             _x += 10;
//             break;
//         case SDLK_UP:
//             _y -= 10;
//             break;
//         case SDLK_DOWN:
//             _y += 10;
//             break;
//         }
//     }
// }

void Square::update(){
    if (Controller::leftIsPressed()){ _x -= 1;};
    if (Controller::upIsPressed()){ _y -= 1;};
    if (Controller::downIsPressed()){ _y += 1;};
    if (Controller::rightIsPressed()){ _x += 1;};
}

//PRIVATE