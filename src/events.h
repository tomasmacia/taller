
#ifndef EVENTS_H_
#define EVENTS_H_
#include <SDL2/SDL.h>
#include "game.h"
#include "Action.h"
#include <map>


class Events{

public:

    //Events(){};
    Events(Game* game, class Character* cody):
        _game(game),_cody(cody){};
    bool keyboard_event();
    static void addHotkey(SDL_Scancode scancode, Action b);
    static void initHotkeys();

private:
    void execute_event();
    Uint32 t = SDL_GetTicks();
    bool up=false ,rigth=false, left=false, down=false, hit=false, jump=false;
    Game* _game;
    class Character* _cody;
    SDL_Event _event;
    Action getBindingForKeyPress(SDL_Scancode scancode);
    static map<SDL_Scancode,Action>* hotkeys;

};


#endif