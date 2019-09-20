
#ifndef EVENTS_H_
#define EVENTS_H_
#include <SDL2/SDL.h>
#include "game.h"
#include "character.h"

class Events{

private:
    Game* _game;
    Character* _cody;
    Uint32 _time;    

    SDL_Event _event;

public:

    Events(Game* game, Character* cody);

    bool keyboard_event();

private:

    void second_event();
};
#endif