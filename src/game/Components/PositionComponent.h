//
// Created by Tomás Macía on 14/10/2019.
//

#ifndef GAME_POSITIONCOMPONENT_H
#define GAME_POSITIONCOMPONENT_H

#include "../../to_remove_or_modify/ECS.h"

class PositionComponent : public Component {
public:
    PositionComponent(int x, int y) ;

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

private:
    int x;
    int y;
};


#endif //GAME_POSITIONCOMPONENT_H
