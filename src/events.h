
#ifndef EVENTS_H_
#define EVENTS_H_
#include <SDL2/SDL.h>
#include "game.h"
#include <map>

enum binding {UP, DOWN, LEFT, RIGHT, JUMP, PUNCH, KICK, JUMP_KICK, NONE, QUIT, CROUCH};

class Events{

public:

    //Events(){};
    Events(Game* game, class Character* cody):
        _game(game),_cody(cody){};
    bool keyboard_event();
    static void addHotkey(SDL_Scancode scancode, binding b);
    static void initHotkeys();

private:
    void execute_event();
    Uint32 t = SDL_GetTicks();
    bool up=false ,rigth=false, left=false, down=false, hit=false, jump=false;
    Game* _game;
    class Character* _cody;
    SDL_Event _event;
    binding getBindingForKeyPress(SDL_Scancode scancode);
    static map<SDL_Scancode,binding>* hotkeys;

};


#endif