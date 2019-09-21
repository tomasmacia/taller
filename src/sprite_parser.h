#include <iostream>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "sprite.h"

class SpriteParser{ //ESTA IMPLEMENTADO COMO PARA QUE UNO LE CARGE UN VECTOR DE PATHS DE SPRITS YA SEPARADOS

private:

    std::vector <Sprite*>* _sprites;
    int _totalSprites;
    int _currentSpriteNumber;

public:
    SpriteParser(std::vector <Sprite*>* sprites);

    Sprite* next();

private:
    void raiseException(std::string mesage);
};