#include "character.h"
#include <SDL2/SDL_image.h>

Character::Character(const std::string &image_path,  int w, int h):
    _x(w*0.4), /*--> posicion x inicial*/
    _w(h*.3),/*--> width que debe tener*/
    _h(h/2),/*-->heigth que debe tener*/
    _y(h/2.475), /*--> posicion y inicial*/
    _h_window( h), /*-->width de window*/
    _w_window( w)/*-->heigth de window*/{
    _pos->x = _x;
    _pos->y = _y;
    _pos->h = _h;
    _pos->w = _w;
    _image = IMG_Load(image_path.c_str());
    if( _image == NULL )	{
	    std::cerr <<  "No pudo cargar imagen.\n";
        std::cerr << "SDL Error: "<< SDL_GetError()<< ".\n";
    	} 
        SDL_SetColorKey(_image, SDL_TRUE,
        SDL_MapRGB(_image->format, 0, 0, 0));
};

bool Character::move(bool movLft,bool movRgth, bool movUp, bool movDwn){ 
        int default_mov = 6;
        if(movLft ){
        //Limites de movimiento harcodeados en relacion a imagen y pantalla
            _x -=default_mov;
            while(_x<0){_x++;} 
        }
        if(movRgth ){
            while(_x>(_w_window/2)-(_w/2)){
                _x--;
                _pos->x= _x;
                _pos->y= _y;
                return true;
                } //(width ventana/2) - (width de la imagen/2) Normalmente llega  ala mitad de la imagen y
            _x +=default_mov;                                        // deberia empieza a moverse el fondo-->Para Futuro
        }    
        if(movUp ){         
            _y -=default_mov;
           while(_y<(_h_window/3)){_y++;}//Normalmente (heigth/3)
        }   
        if(movDwn){
            _y +=default_mov;
            while(_y>(_h_window/2)){_y--;} //(heigth/2)
        }
        _pos->x= _x;
        _pos->y= _y;
        return false;
};

    void Character::updateImage(SDL_Window* window){

        SDL_Surface* gScreenSurface = SDL_GetWindowSurface(window);
        SDL_BlitScaled(_image,NULL, gScreenSurface,_pos);
        SDL_FreeSurface(gScreenSurface);
        };




