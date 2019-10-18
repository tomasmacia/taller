//
// Created by Tomás Macía on 14/10/2019.
//

#ifndef GAME_POSITIONCOMPONENT_H
#define GAME_POSITIONCOMPONENT_H

#include "ECS.h"

class PositionComponent : public Component {
public:
    PositionComponent(Entity *camera, int x, int y) ;
    PositionComponent(Entity *camera);
    PositionComponent(){}

    void init() override {
        setPosition(0, 0);
    }

    void setPosition(int xPos, int yPos) {
        this->x = xPos;
        this->y = yPos;
    }

    bool changed();

    int getX() {
        return x;
    }

    int getY() {
        return y;
    }

    Entity* getCamera() {
        return camera;
    }

private:
    int x;
    int y;

    Entity *camera;
};


#endif //GAME_POSITIONCOMPONENT_H
