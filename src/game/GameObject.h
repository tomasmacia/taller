//
// Created by Tomás Macía on 21/09/2019.
//

#ifndef GAME_GAMEOBJECT_H
#define GAME_GAMEOBJECT_H

#include <SDL2/SDL_render.h>
#include "PhysicsComponent.h"
#include "GraphicsComponent.h"

class GameObject {

private:

    GraphicsComponent* graphicsComponent;
    PhysicsComponent* physicsComponent;

public:
    GameObject(const char* textureFile, int x, int y);
    GameObject() = default;

    virtual ~GameObject() = default;;

    virtual void update() = 0;
    virtual void render() = 0;
};

#endif //GAME_GAMEOBJECT_H