#ifndef GAME_TOCLIENTPACK_H_
#define GAME_TOCLIENTPACK_H_

#include <SDL2/SDL.h>
#include <string>
#include <map>

#include "../../image/TextureWrapper.h"

class ToClientPack {
    
    public:
        ToClientPack(std::string path, SDL_Rect srcRect, SDL_Rect destRect, bool isFliped);
        ToClientPack(); //NULL PATTERN

        //GETTERS
        //===============================
        void render(std::map<std::string, TextureWrapper*>* loadedTexturesMap);

        //GETTERS
        //===============================
        std::string getPath(){
            return path;
        }

        SDL_Rect getSrcRect() {
        return srcRect;
        }

        SDL_Rect getDstRect() {
        return destRect;
        }

        bool getFliped() {
        return fliped;
        }

    private:
    //ATRIBUTES
    //===============================
    std::string path;
    SDL_Rect destRect;
    SDL_Rect srcRect;
    bool fliped;
};

#endif