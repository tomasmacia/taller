//
// Created by Tomás Macía on 21/09/2019.
//

#ifndef GAME_TEXTUREMANAGER_H
#define GAME_TEXTUREMANAGER_H

#include <SDL2/SDL_render.h>

class TextureManager {
public:
    static SDL_Texture* loadTexture(const char* textureFile);
};

#endif //GAME_TEXTUREMANAGER_H
