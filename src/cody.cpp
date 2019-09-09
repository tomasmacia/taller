#include "cody.h"
#include "SDL2/SDL.h"

//CONSTRUCTOR & DESTRUCTOR

Cody::Cody( int x, int w, int h):
 _x(x), _y(h/2.475), _h(h),_w(w){
    //La posicion es siempre 0 en X
    // En Y es (heigth/2.475)->Numero que sirve para las
    //resoluciones 4:3
    //El rect tiene las posicion y alto(heigth ventana/2) y ancho(heigth ventana*.3) del pj 
    _rectangle.x = _x;
    _rectangle.y = _y;
    _rectangle.h = _h/2;
    _rectangle.w = _h*.3;
}

//PUBLIC

void Cody::move(bool movLft,bool movRgth, bool movUp, bool movDwn){ 
        int default_mov = 10;
        if(movLft ){
        //Limites de movimiento harcodeados en relacion a imagen y pantalla
        // Buscar Fix
            _x -=default_mov;
            while(_x<0){_x++;} 
        }
        if(movRgth ){
            _x +=default_mov;
            while(_x>(_w/2)-(_rectangle.w/2)){_x--;} //(width ventana/2) - (width de la imagen/2) Normalmente llega  ala mitad de la imagen y
                                                    // deberia empieza a moverse el fondo-->Para Futuro
        }    
        if(movUp ){         
            _y -=default_mov;
           while(_y<(_h/3)){_y++;}//Normalmente (heigth/3)
        }   
        if(movDwn){
            _y +=default_mov;
            while(_y>(_h/2)){_y--;} //(heigth/2)
        }
    _rectangle.x = _x;
    _rectangle.y = _y;
    }

const SDL_Rect Cody::getPosition(){
    return _rectangle;
}

//PRIVATE