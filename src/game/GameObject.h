//
// Created by Tomás Macía on 21/09/2019.
//

#ifndef GAME_GAMEOBJECT_H
#define GAME_GAMEOBJECT_H

#include <SDL2/SDL_render.h>

class GameObject {
public:
    GameObject(const char* textureFile, int x, int y);
    ~GameObject();

    void update();
    void render();

private:
    int x;
    int y;
    int velocity;

    SDL_Texture *texture;
    SDL_Rect sourceRect;
    SDL_Rect destinationRect;
};

#endif //GAME_GAMEOBJECT_H
