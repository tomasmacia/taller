//
// Created by Tomás Macía on 14/10/2019.
//

#ifndef GAME_POSITION_H
#define GAME_POSITION_H

#include "collition/CollitionHandler.h"

class Position {
public:
    Position(int x, int y, int z, CollitionHandler* collitionHandler) ;

    void ifValidChangeTo(int newX, int newY, int newZ);

    void setPosition(int xPos, int yPos, int zPos) {
        this->x = xPos;
        this->y = yPos;
        this->z = zPos;
    }

    int getX() {
        return x;
    }

    int getY() {
        return y;
    }

    int getZ() {
        return z;
    }
private:

    int x;
    int y;
    int z;

    CollitionHandler* _collitionHandler = nullptr;
};


#endif //GAME_POSITION_H
