
#ifndef EVENTS_H_
#define EVENTS_H_
#include <SDL2/SDL.h>
#include "game.h"

class Events{

public:

    //Events(){};
    Events(Game* game, class Character* cody):
        _game(game),_cody(cody){};
    bool keyboard_event();


private:
    Game* _game;
    class Character* _cody;
    SDL_Event _event;
    Uint32 _time;    
    
    void second_event();
};

#endif