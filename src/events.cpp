#include "events.h"
#include <iostream>

bool Events::quit()
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
            }                 
        default:
            return false;
        }
    }
    return false;
}