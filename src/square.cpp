#include "square.h"
#include "window.h"

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

void Square::move(bool movLft,bool movRgth, bool movUp, bool movDwn){ //HARDCODEADO
        int default_mov = 10;
        if(movLft){
            _x -=default_mov;
        }
        if(movRgth){
            _x +=default_mov;
        }  
        if(movUp){
            _y -=default_mov;
        }   
        if(movDwn){
            _y +=default_mov; 
        }
    //    this->display();   
    }

//PRIVATE