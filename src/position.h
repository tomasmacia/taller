#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "square.h"

class Position{

private:
    float _x;
    float _y;
    Square* _square;

public:
    Position(float x,float y,Square* square);
    ~Position();

    void changeXBy(float amount);
    void changeYBy(float amount);
private:
};