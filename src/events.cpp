#include "events.h"
#include <iostream>
#include "square.h"

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
                case(SDL_SCANCODE_LCTRL):
                    std::cerr << "Left Control.\n";
                    return false;
                /*No me reconoce espacio*/
                case(SDL_SCANCODE_BACKSPACE):
                    std::cerr << "Espacio.\n";
                    return false;
                case SDL_SCANCODE_LEFT:
                    _avatar->move(true,false,false,false);
                    return false;
                case SDL_SCANCODE_RIGHT:
                    _avatar->move(false,true,false,false);
                    return false;
                case SDL_SCANCODE_UP:
                    _avatar->move(false,false,true,false);
                    return false;
                case SDL_SCANCODE_DOWN:
                    _avatar->move(false,false,false,true);
                    return false;;
                }
                             
            default:
                return false;
        }
    }
    return false;
}