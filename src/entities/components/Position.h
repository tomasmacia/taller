//
// Created by Tomás Macía on 14/10/2019.
//

#ifndef GAME_POSITION_H
#define GAME_POSITION_H

#include "collition/CollitionHandler.h"
#include "../components/Point.h"

class Position {
public:
    Position(int x, int y, int z, CollitionHandler* collitionHandler) ;
    ~Position();

    void tryToMoveTo(int newX, int newY, int newZ);

    void setPosition(int xPos, int yPos, int zPos) {
        point.x = xPos;
        point.y = yPos;
        point.z = zPos;
    }

    int getX() {
        return point.x;
    }

    int getY() {
        return point.y;
    }

    int getZ() {
        return point.z;
    }
private:
    Point* point = nullptr;
    CollitionHandler* _collitionHandler = nullptr;
};


#endif //GAME_POSITION_H
