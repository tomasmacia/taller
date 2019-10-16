//
// Created by Tomás Macía on 14/10/2019.
//

#ifndef GAME_POSITIONCOMPONENT_H
#define GAME_POSITIONCOMPONENT_H

#include "ECS.h"

class PositionComponent : public Component {
public:
    PositionComponent(Entity *camera);

    void update();
    void init(){
        setPosition(0, 0);
    }

    ~PositionComponent(){}

    void setPosition(int xPos, int yPos) {
        this->x = xPos;
        this->y = yPos;
    }

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
