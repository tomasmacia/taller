#include <SDL2/SDL.h>

class Events{

public:

    //Events(){};
    Events(class Square* avatar):
        _avatar(avatar)
    {};
    bool keyboard_event();

private:
    class Square* _avatar = nullptr;
    SDL_Event _event;
};