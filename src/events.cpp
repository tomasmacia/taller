#include "events.h"
#include <iostream>
#include "cody.h"


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
                    _avatar->move(true,false,false,false);
                    std::cerr << "Left.\n";
                    return false;
                case SDL_SCANCODE_RIGHT:
                    _avatar->move(false,true,false,false);
                    std::cerr << "Right.\n";
                    return false;
                case SDL_SCANCODE_UP:
                    _avatar->move(false,false,true,false);
                    std::cerr << "UP.\n";
                    return false;
                case SDL_SCANCODE_DOWN:
                    _avatar->move(false,false,false,true);
                    std::cerr << "DOWN.\n";
                    return false;
            }
    //Buscar forma de reaizar movimiento lateral o como realizar acciones(saltar, golpear, etc)
   /*         switch (_event.key.keysym.scancode)
            {    
                case (SDL_SCANCODE_DOWN & SDL_SCANCODE_RIGHT):
                    _avatar->move(false,true,false,true);
                    std::cerr << "DOWN AND RIGTH.\n";
                    return false;
                case (SDL_SCANCODE_DOWN & SDL_SCANCODE_LEFT):
                    _avatar->move(true,false,false,true);
                    std::cerr << "DOWN AND LEFT.\n";
                    return false;
                case (SDL_SCANCODE_UP & SDL_SCANCODE_RIGHT):
                    _avatar->move(false,true,false,true);
                    std::cerr << "DOWN AND RIGTH.\n";
                    return false;              
                }    */                     
            default:
                return false;
        }    
        return false;
    }
    return false;
}