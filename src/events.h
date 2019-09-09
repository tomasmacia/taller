#include <SDL2/SDL.h>

class Events{

public:

    //Events(){};
    Events(class Cody* avatar):
        _avatar(avatar)
    {};
    bool keyboard_event();

private:
    class Cody* _avatar = nullptr;
    SDL_Event _event;
};