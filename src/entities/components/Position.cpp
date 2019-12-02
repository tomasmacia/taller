//
// Created by Tomás Macía on 14/10/2019.
//
#include "Position.h"

Position::Position(int x, int y, int z, CollitionHandler* collitionHandler) {

    point = new Point(x,y,z);
    _collitionHandler = collitionHandler;
}

void Position::ifValidChangeTo(int newX, int newY, int newZ) {

    int prevX, prevY, prevZ, correctedX, correctedY, correctedZ;

    prevX = point->x;
    prevY = point->y;
    prevZ = point->z;

    setPosition(newX,newY,newZ);
    _collitionHandler->moveCollitionBoxes(this);

    if (_collitionHandler->anyCollitions()){

        Point* corrected = _collitionHandler->getCorrected();

        setPosition(corrected->x,corrected->y,corrected->z);
        _collitionHandler->moveCollitionBoxes(this);
    }
}

Position::~Position() {
    delete (point);
}
