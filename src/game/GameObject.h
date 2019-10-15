//
// Created by Tomás Macía on 21/09/2019.
//

#ifndef GAME_GAMEOBJECT_H
#define GAME_GAMEOBJECT_H

#include "PhysicsComponent.h"
#include "GraphicsComponent.h"

class GameObject {

protected:

    PhysicsComponent* _physicsComponent;
    GraphicsComponent* _graphicsComponent;

public:
    GameObject(int xPos, int yPos, int width, int height);
    GameObject() = default;

    virtual ~GameObject() = default;;

    virtual void update() = 0;
    virtual void render() = 0;
};

#endif //GAME_GAMEOBJECT_H