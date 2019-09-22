#ifndef EVENT_HANDLER_H_
#define EVENT_HANDLER_H_

#include <SDL2/SDL.h>
#include "game.h"
#include "character.h"

class EventHandler{

private:
    Character* _cody;
    class Game* _game;
    SDL_Event _event;

public:
    EventHandler(class Game* game, Character* cody);

    void handleAllEventsInQueue();
    void execute_event();
};
#endif