#include "square.h"
#include "SDL2/SDL.h"

//CONSTRUCTOR & DESTRUCTOR
Square::Square(int side, int x, int y):
_side(side), _x(x), _y(y){
    _rectangle.x = _x;
    _rectangle.y = _y;


}
//PUBLIC

void Square::move(bool movLft,bool movRgth, bool movUp, bool movDwn){ 
        int default_mov = 6;
        if(movLft ){
        //Limites de movimiento harcodeados en relacion a imagen y pantalla
        // Buscar Fix
            _x -=default_mov;
            while(_x<0){_x++;}
        }
        if(movRgth ){
            _x +=default_mov;
            while(_x>130){_x--;} //(width/2) Normalmente llega  ala mitad de la imagen y
                                // empieza a moverse el fondo
        }    
        if(movUp ){         
            _y -=default_mov;
            while(_y<65){_y++;}
        }   
        if(movDwn){
            _y +=default_mov;
            while(_y>99){_y--;} //(heigth/2)
        }
    _rectangle.x = _x;
    _rectangle.y = _y;
    }

const SDL_Rect Square::getPosition(){
    return _rectangle;
}

//PRIVATE