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

    private:
        std::string path;   //un string
        SDL_Rect destRect;  //4 int
        SDL_Rect srcRect;   //4 int
        bool fliped;        //1 int (1 o 0)
};      //PODEMOS USAR ESTO PARA MANDAR TEXTO EN VEZ DE SERIALIZAR EL OBJETO

#endif