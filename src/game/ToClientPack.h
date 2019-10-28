#ifndef GAME_TOCLIENTPACK_H_
#define GAME_TOCLIENTPACK_H_

#include <SDL2/SDL.h>
#include "TextureWrapper.h"
#include <string>

class ToClientPack {
    
    public:
        ToClientPack(std::string path, SDL_Rect srcRect, SDL_Rect destRect);
        std::string getPath();
        SDL_Rect getSourceRect();
        SDL_Rect getDestinationRect();
        TextureWrapper asTextureWrapper();

    private:
        std::string path;
        SDL_Rect destRect;
        SDL_Rect srcRect;
};

//expected declaration?
#endif