#include <iostream>
#include <SDL2/SDL.h>
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
void EventHandler::execute_event(){
    switch (_event.type)
    {
    case SDL_QUIT:
        _game->close();
        break;
    case SDL_KEYDOWN:
        if(_event.key.repeat == 0 ){
            switch (_event.key.keysym.scancode)
            {
                case(SDL_SCANCODE_ESCAPE): 
                    _game->close();
                case SDL_SCANCODE_LEFT:
                    _cody->enableLeftMovement();
                    break;
                case SDL_SCANCODE_RIGHT:
                    _cody->enableRightMovement();
                    break;
                case SDL_SCANCODE_UP:
                    _cody->enableDeepIntoScreenMovement();
                    break;
                case SDL_SCANCODE_DOWN:
                    _cody->enableCloserToScreenMovement();
                    break;
                case SDL_SCANCODE_LCTRL:
                    _cody->jump();      //cody ignora si ya esta saltando
                    break;
                case SDL_SCANCODE_X:
                    _cody->hit();       //cody ignora si ya esta golpeando
                    break;
                case SDL_SCANCODE_Z:
                    _cody->crouch();    //cody ignora si ya se esta agachando
                    break;
            }
        }
        break;
    case SDL_KEYUP:
        switch (_event.key.keysym.scancode)
        {
        case SDL_SCANCODE_LEFT:
            _cody->disableLeftMovement();
            break;
        case SDL_SCANCODE_RIGHT:
            _cody->disableRightMovement();
            break;
        case SDL_SCANCODE_UP:
            _cody->disableDeepIntoScreenMovement();
            break;
        case SDL_SCANCODE_DOWN:
            _cody->disableCloserToScreenMovement();
            break;
        }
        break;
    } 
}
//PRIVATE