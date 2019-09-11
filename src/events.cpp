#include "events.h"
#include <iostream>
#include <SDL2/SDL.h>
#include "character.h"

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
                    _cody->move(true,false,false,false);
                    std::cerr << "Left.\n";
                    return false;
                case SDL_SCANCODE_RIGHT:
                    if (_cody->move(false,true,false,false)){
                        _game->move_all();
                    };
                    std::cerr << "Right.\n";
                    return false;
                case SDL_SCANCODE_UP:
                    _cody->move(false,false,true,false);
                    std::cerr << "UP.\n";
                    return false;
                case SDL_SCANCODE_DOWN:
                    _cody->move(false,false,false,true);
                    std::cerr << "DOWN.\n";
                    return false;
            }                   
            default:
                return false;
        }    
        return false;
    }
    return false;
}