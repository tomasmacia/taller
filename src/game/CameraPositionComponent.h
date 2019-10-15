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
//        this->windowWidth = Game::getInstance().getConfig()->screenResolution.width;
//        this->windowHeight = Game::getInstance().getConfig()->screenResolution.height;
        this->windowWidth = 15;
        this->windowHeight = 15;
        this->levelWidth = 100;
        this->levelHeight = 100;
        this->marginWidth = 10;
    }


    ~CameraPositionComponent() override {};

private:
    int currentX;
    int windowHeight, windowWidth;
    int levelHeight, levelWidth;
    int marginWidth;

    Entity& player;

    bool shouldMoveCamera(int);

    void moveCamera(int);
};


#endif //GAME_CAMERAPOSITIONCOMPONENT_H
