#include <iostream>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class SpriteParser{ //ESTA IMPLEMENTADO COMO PARA QUE UNO LE CARGE UN VECTOR DE PATHS DE SPRITS YA SEPARADOS

private:

    std::vector <std::string> _spritePaths;
    int _totalSprites;
    int _currentSpriteNumber;

public:
    SpriteParser(std::vector <std::string>& spritePaths);

    std::string next();

private:
    void raiseException(std::string mesage);
};