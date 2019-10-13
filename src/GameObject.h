//
// Created by Tomás Macía on 21/09/2019.
//

#ifndef GAME_GAMEOBJECT_H
#define GAME_GAMEOBJECT_H

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_rect.h>

class GameObject {
public:
    GameObject(const char* textureFile, int x, int y);
    GameObject() = default;
    virtual ~GameObject() = 0;

    virtual void update() = 0;
    virtual void render() = 0;

private:
    int x = 0;
    int y = 0;

    SDL_Texture *texture = nullptr;
    SDL_Rect sourceRect;
    SDL_Rect destinationRect;
};

#endif //GAME_GAMEOBJECT_H