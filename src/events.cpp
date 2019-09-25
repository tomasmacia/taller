#include "events.h"
#include <iostream>
#include <SDL2/SDL.h>
#include "character.h"
/* Funcionales son los movimientos (no laterales)
con las flechas, saltar con LCTRL, golpear con X y agacharse con Z*/
bool Events::keyboard_event()
{   


    execute_event();
    if (SDL_PollEvent(&_event)) 
    {
        switch (_event.type)
        {
    /*Click en la X*/
        case SDL_QUIT:
            std::cerr <<"Click en X.\n";
            return true;
    /*Aprete escape*/
        case SDL_KEYDOWN:
            switch (_event.key.keysym.scancode)
            {
                case(SDL_SCANCODE_ESCAPE): 
                    std::cerr << "Escape.\n";
                    return  true;
                case SDL_SCANCODE_LEFT:
                   left =true;
                 _cody->setFlip(SDL_FLIP_HORIZONTAL);
                    return false;
                case SDL_SCANCODE_RIGHT:
                    rigth = true;
                    _cody->setFlip(SDL_FLIP_NONE);
           //       solo me interesa la derecha
                    return false;
                case SDL_SCANCODE_UP:
                    up = true;
                    return false;
                case SDL_SCANCODE_DOWN:
                    down = true;
                    return false;
                case SDL_SCANCODE_LCTRL:
                //Aviso si se presiona rigth o left antes de saltar
                    if (rigth){_cody->mov_jump(0);}
                    if (left) {_cody->mov_jump(1);}
                    _cody->move(1,-1);
                    return false;
                case SDL_SCANCODE_X:
                    _cody->move(2,-1);
                    return false;
                case SDL_SCANCODE_Z:
                   _cody->move(3,-1);
                    return false;
                case SDL_SCANCODE_C:
                  //Aviso si se presiona rigth o left antes de salta
                if (rigth){ _cody->mov_jump(0);}
                if (left) {_cody->mov_jump(1);}
                    _cody->move(5,-1);
                    return false;
                case SDL_SCANCODE_A:
                    _cody->move(6,-1);    
                    return false;
                default:
                    return false;
            }                   
        case SDL_KEYUP:
            switch (_event.key.keysym.scancode)
            {
                case SDL_SCANCODE_LEFT:
                   left =false;
                    return false;
                case SDL_SCANCODE_RIGHT:
                    rigth = false;
                    return false;
                case SDL_SCANCODE_UP:
                    up = false;
                    return false;
                case SDL_SCANCODE_DOWN:
                    down = false;
                    return false;
                case SDL_SCANCODE_X:
                    return false;
                case SDL_SCANCODE_LCTRL:
                    return false;
            default:
                return false;
            }
        }  
        return false;
    }
    return false;
}


void Events::execute_event(){
 
  
    if (up){_cody->move(0,8);}
    if (rigth) {_cody->move(0,6);}
    if (left){_cody->move(0,4);}
    if(down){_cody->move(0,2);}
}
