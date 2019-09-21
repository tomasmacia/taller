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
void EventHandler::execute_event()
{   
    execute_event();
    if (SDL_PollEvent(&_event)) 
    {
        switch (_event.type)
        {
        case SDL_QUIT:
            _game->close();
        case SDL_KEYDOWN:
            switch (_event.key.keysym.scancode)
            {
                case(SDL_SCANCODE_ESCAPE): 
                    _game->close();
                case SDL_SCANCODE_LEFT:
                    _cody->moveLeft();
                    break;
                case SDL_SCANCODE_RIGHT:
                    _cody->moveRight();
                    break;
                case SDL_SCANCODE_UP:
                    _cody->moveDeepIntoScreen();
                    break;
                case SDL_SCANCODE_DOWN:
                    _cody->moveCloserToScreen();
                    break;
                case SDL_SCANCODE_LCTRL:
                    _cody->jump();
                    break;
                case SDL_SCANCODE_X:
                    _cody->hit();
                    break;
                case SDL_SCANCODE_Z:
                    _cody->crouch();
                    break;
            }                   
        }  
    }
}
//PRIVATE