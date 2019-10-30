#ifndef GAME_TOCLIENTPACK_H_
#define GAME_TOCLIENTPACK_H_

#include <SDL2/SDL.h>
#include <string>
#include <map>

#include "TextureWrapper.h"

class ToClientPack {
    
    public:
        ToClientPack(std::string path, SDL_Rect srcRect, SDL_Rect destRect, bool isFliped);
        ToClientPack(); //NULL PATTERN

        void render(std::map<std::string, TextureWrapper*> loadedTexturesMap);
        std::string getPath();
        SDL_Rect getSrcRect();
        SDL_Rect getDstRect();
        bool getFliped();

    private:
        std::string path;
        SDL_Rect destRect;
        SDL_Rect srcRect;
        bool fliped;
};

#endif