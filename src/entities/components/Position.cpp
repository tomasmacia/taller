//
// Created by Tomás Macía on 14/10/2019.
//
#include "Position.h"

Position::Position(int x, int y, int z, CollitionHandler* collitionHandler) {
    setPosition(x,y,z);
    _collitionHandler = collitionHandler;
}

int Position::getXInTwoDimentions() {
    return x;
}

int Position::getYIinTwoDimentions() {
    return screenHegiht - (y + z);
}

void Position::ifValidChangeTo(int newX, int newY, int newZ) {

    int prevX = x;
    int prevY = y;
    int prevZ = z;

    setPosition(newX,newY,newZ);
    _collitionHandler->moveCollitionBoxes(this);

    if (_collitionHandler->anyCollitions()){
        setPosition(prevX,prevY,prevZ);
        _collitionHandler->moveCollitionBoxes(this);
    }
}
