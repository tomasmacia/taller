#include <iostream>
#include <SDL2/SDL.h>
#include "character.h"
#include "event_handler.h"


//CONSTRUCTOR & DESTRUCTOR
EventHandler::EventHandler(Game* game, class Character* cody):
        _game(game),_cody(cody){};

//PUBLIC
void EventHandler::handleAllEventsInQueue(){
    while( SDL_PollEvent( &_event ) != 0 ){
        execute_event();
    }
}

/* Funcionales son los movimientos (no laterales)
con las flechas, saltar con LCTRL, golpear con X y agacharse con Z*/
void EventHandler::execute_event()
{   
    execute_event();
    if (SDL_PollEvent(&_event)) 
    {
        switch (_event.type)
        {
    /*Click en la X*/
        case SDL_QUIT:
            std::cerr <<"Click en X.\n";
    /*Aprete escape*/
        case SDL_KEYDOWN:
            switch (_event.key.keysym.scancode)
            {
                case(SDL_SCANCODE_ESCAPE): 
                    std::cerr << "Escape.\n";
                case SDL_SCANCODE_LEFT:
                   _cody->move(0,4);
                 _cody->setFlip(SDL_FLIP_HORIZONTAL);
                case SDL_SCANCODE_RIGHT:
                    _cody->move(0,6);
                    _cody->setFlip(SDL_FLIP_NONE);
           //       solo me interesa la derecha
                case SDL_SCANCODE_UP:
                    _cody->move(0,8);
                case SDL_SCANCODE_DOWN:
                    _cody->move(0,2);;
                case SDL_SCANCODE_LCTRL:
                    _cody->move(1,-1);
                case SDL_SCANCODE_X:
                    _cody->move(2,-1);
                case SDL_SCANCODE_Z:
                   _cody->move(3,-1);
            }                   
        case SDL_KEYUP:
            switch (_event.key.keysym.scancode)
            {
                case SDL_SCANCODE_LEFT:
                   left =false;
                case SDL_SCANCODE_RIGHT:
                    rigth = false;
                case SDL_SCANCODE_UP:
                    up = false;
                case SDL_SCANCODE_DOWN:
                    down = false;
                case SDL_SCANCODE_X:
                case SDL_SCANCODE_LCTRL:
            }
        }  
    }
}
//PRIVATE