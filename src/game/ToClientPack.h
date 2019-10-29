#ifndef GAME_TOCLIENTPACK_H_
#define GAME_TOCLIENTPACK_H_

#include <SDL2/SDL.h>
#include "TextureWrapper.h"
#include <string>

class ToClientPack {
    
    public:
        ToClientPack(std::string path, SDL_Rect srcRect, SDL_Rect destRect, bool isFliped){
            this->path = path;
            this->srcRect = srcRect;
            this->destRect = destRect;
            this->fliped = isFliped;
        }
        ToClientPack(){ //NULL PATTERN
            SDL_Rect aux;
            this->path = "NULL";
            this->srcRect = aux;
            this->destRect = aux;
            this->fliped = false;
        }

        std::string getPath(){
            return path;
        }

        SDL_Rect getSourceRect();
        SDL_Rect getDestinationRect();
        TextureWrapper asTextureWrapper();
        bool getFliped();

    private:
        std::string path;
        SDL_Rect destRect;
        SDL_Rect srcRect;
        bool fliped;
};

//expected declaration?
#endif