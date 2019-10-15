//
// Created by Tomás Macía on 14/10/2019.
//

#ifndef GAME_CAMERACOMPONENT_H
#define GAME_CAMERACOMPONENT_H

#include "ECS.h"
#include "Game.h"


class CameraComponent : public Component {
public:
    void update() override;
    void render() override {};
    void init() override {
        this->windowWidth = Game::getInstance().getConfig()->screenResolution.width;
        this->windowHeight = Game::getInstance().getConfig()->screenResolution.height;
        this->marginWidth = 100;
        this->levelWidth = 0;
        this->levelHeight = 0;
    };

    void setLevelWidthAndHeight(int w, int h) {
        this->levelWidth = w;
        this->levelHeight = h;
    }

    ~CameraComponent() override {};

private:
    int currentX;
    int levelWidth, levelHeight;
    int windowWidth, windowHeight;
    int marginWidth;


    bool shouldMoveCamera(int);

    void moveCamera(int);
};


#endif //GAME_CAMERACOMPONENT_H
