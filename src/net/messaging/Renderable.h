#ifndef GAME_RENDERABLE_H_
#define GAME_RENDERABLE_H_

#include <string>
#include <map>

#include "../../image/TextureWrapper.h"
#include "../../image/Rect.h"

class Renderable {
    
public:
    Renderable(std::string path, Rect srcRect, Rect destRect, bool isFliped);

    void render(std::map<std::string, TextureWrapper*>* loadedTexturesMap);

    //GETTERS
    //===============================
    std::string getPath(){
        return path;
    }

    Rect getSrcRect() {
    return srcRect;
    }

    Rect getDstRect() {
    return destRect;
    }

    bool getFliped() {
    return fliped;
    }

private:
    //ATRIBUTES
    //===============================
    std::string path;
    Rect destRect;
    Rect srcRect;
    bool fliped;
};

#endif