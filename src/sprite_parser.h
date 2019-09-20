#include <iostream>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class SpriteParser{

private:

    std::vector <std::string> _spritePaths;

public:
    SpriteParser(std::vector <std::string>& spritePaths);
    ~SpriteParser();

    SDL_Texture* next();
    void update();

private:
    void raiseException(std::string mesage);
};