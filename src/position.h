#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "appearance.h"

class Position{

private:
    float _x;
    float _y;
    Appearance* _appearance;

public:
    Position(float x,float y,Appearance* appearance);
    ~Position();

    void changeXBy(float amount);
    void changeYBy(float amount);
private:
};