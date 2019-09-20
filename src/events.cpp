#include "events.h"
#include <iostream>
#include <SDL2/SDL.h>
#include "character.h"
/* Funcionales son los movimientos (no laterales)
con las flechas, saltar con LCTRL, golpear con X y agacharse con Z*/
bool Events::keyboard_event()
{   


    second_event();
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
                    int t;
                    if (rigth){t= 1;}
                    if (left){t = 0;}
                    if (_cody->move(1,t))
                    {
                        _game->move_all();
                    }
                    return false;
                case SDL_SCANCODE_X:
                    hit =true;
                    return false;
                case SDL_SCANCODE_Z:
                   _cody->move(3,-1);
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
                    hit =false;
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



void Events::second_event(){
 
  //  if(jump){
    //    _cody->move(1,1);
    //}
    if(hit){
        rigth=left=false;
        _cody->move(2,-1);
      //  rigth=r;
       // left=l;
        }
    if (up){_cody->move(0,8);}
    if (rigth) {                    
        if (_cody->move(0,6))
        {
            _game->move_all();
        }
    }
    if (left){_cody->move(0,4);}
    if(down){_cody->move(0,2);}
}
