#include <SDL2/SDL.h>
#include "game.h"

class EventHandler{

private:
    Character* _cody;
    Game* _game;
    SDL_Event _event;

public:
    EventHandler(Game* game, Character* cody);

    void handleAllEventsInQueue();
    void execute_event();
}