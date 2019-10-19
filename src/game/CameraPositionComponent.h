//
// Created by Tomás Macía on 14/10/2019.
//

#ifndef GAME_CAMERAPOSITIONCOMPONENT_H
#define GAME_CAMERAPOSITIONCOMPONENT_H


#include "ECS.h"
#include "Game.h"

class CameraPositionComponent : public Component {
public:

    void update() override;
    void init() override {
        this->currentX = 0;
        this->windowWidth = Game::getInstance().getConfig()->screenResolution.width;
        this->windowHeight = Game::getInstance().getConfig()->screenResolution.height;
        this->levelWidth = Game::getInstance().getCurrentLevelWidth();
        this->levelHeight = Game::getInstance().getConfig()->screenResolution.height;
        this->marginWidth = windowWidth/4;
    }

    void setPlayer(Entity* player);

    int currentX;

    ~CameraPositionComponent() override {};

private:
    int _scroll_amount;

    int windowHeight, windowWidth;
    int levelHeight, levelWidth;
    int marginWidth;

    std::list<Entity*> _players;

    bool shouldMoveCamera();
    bool marginSurpased();
    bool notAtTheEnd();
    bool noPlayerInLeftLimit();
    bool inLeftLimit(Entity* player);
    bool touchingMargin(Entity* player);

    void scroll();
};


#endif //GAME_CAMERAPOSITIONCOMPONENT_H
