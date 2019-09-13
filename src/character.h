#ifndef CHARACTER_H_
#define CHARACTER_H_
#include "iostream"
#include <SDL2/SDL.h>
#include "string.h"

class Character {
public:
    Character(const std::string &image_path, int w, int h);
    bool move(int option);
    void updateImage(SDL_Window* window);
    void sprite();
private:
    int  _x,_y,_w,_h,_w_window,_h_window;
    int  cont=0;// contador para cambiar de imagen;
    const int change = 3;// constante para cambiar de imagen
    int cant_img_sprite=1;//imagenes en una tira de sprite
    int spriteToload = 0;//en que imagen de la tira estoy
    int loop = 3;//cantidad de loop que deben suceder para que una accion pase a la
                    // imagen del sprite
    SDL_Surface* _image; 
    SDL_Rect* _pos = new SDL_Rect;//rect para colocar en lugar correcto del window
    SDL_Rect* rect = new SDL_Rect; //rect para elegir imagen exacta de tira de sprite
    int state = -1 , state_previous = -1;//estado actual y previo del pj(acciones)
};
 
#endif