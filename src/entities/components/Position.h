//
// Created by Tomás Macía on 14/10/2019.
//

#ifndef GAME_POSITION_H
#define GAME_POSITION_H

#include "../../to_remove_or_modify/ECS.h"

class Position {
public:
    Position(int x, int y, int z) ;

    int getX() {
        return x;
    }

    int getY() {
        return y;
    }

    int getZ() {
        return z;
    }

    void ifValidChangeTo(int newX, int newY, int newZ){

    }

private:
    void setPosition(int xPos, int yPos, int zPos) {
        this->x = xPos;
        this->y = yPos;
        this->z = zPos;
    }

    int x;
    int y;
    int z;
};


#endif //GAME_POSITION_H
