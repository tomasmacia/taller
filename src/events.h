#include <SDL2/SDL.h>

class Events{

public:
    Events(){};
    bool quit();
    void moveThing();

private:
    
    SDL_Event _event;
};