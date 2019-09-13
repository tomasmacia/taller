#include "events.h"
#include <iostream>
#include <SDL2/SDL.h>
#include "character.h"
/* Funcionales son los movimientos (no laterales)
con las flechas, saltar con LCTRL y golpear con X */
bool Events::keyboard_event()
{   
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
                    _cody->move(0);
      //              std::cerr << "Left.\n";
                    return false;
                case SDL_SCANCODE_RIGHT:
                    if (_cody->move(1))
                    {
                        _game->move_all();
                    };
           //       solo me interesa la derecha
                    return false;
                case SDL_SCANCODE_UP:
                    _cody->move(2);
        //            std::cerr << "UP.\n";
                    return false;
                case SDL_SCANCODE_DOWN:
                    _cody->move(3);
        //            std::cerr << "DOWN.\n";
                    return false;
                case SDL_SCANCODE_LCTRL:
                    _cody->move(4);
       //             std::cerr <<"JUMP\n";
                    return false;
                case SDL_SCANCODE_X:
                    _cody->move(5);
        //            std::cer << "PUNCH\n";
                    return false;
            }                   
            default:
                return false;
        }    
        return false;
    }
    return false;
}