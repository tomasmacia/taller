//
// Created by Tomás Macía on 14/10/2019.
//

#ifndef GAME_CAMERAPOSITIONCOMPONENT_H
#define GAME_CAMERAPOSITIONCOMPONENT_H


#include "ECS.h"
#include "Game.h"

class CameraPositionComponent : public Component {
public:
    CameraPositionComponent(Entity &player): player(player) {}


    void update() override;
    void init() override {
        this->currentX = 0;
        this->windowWidth = Game::getInstance().getConfig()->screenResolution.width;
        this->windowHeight = Game::getInstance().getConfig()->screenResolution.height;
        this->levelWidth = 1600;
        this->levelHeight = 600;
        this->marginWidth = 200;
    }

    int currentX;

    ~CameraPositionComponent() override {};

private:

    int windowHeight, windowWidth;
    int levelHeight, levelWidth;
    int marginWidth;

    Entity& player;

    bool shouldMoveCamera(int);

    void moveCamera(int);
};


#endif //GAME_CAMERAPOSITIONCOMPONENT_H
