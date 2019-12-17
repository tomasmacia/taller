//
// Created by Tomás Macía on 14/10/2019.
//
#include <iostream>
#include "Position.h"
#include "collition/AnimatedEntityCollitionHandler.h"

Position::Position(int x, int y, int z, CollitionHandler* collitionHandler) {

    point = new Point(x,y,z);
    _collitionHandler = collitionHandler;
}

Point *Position::get() {
    return point;
}

void Position::tryToMoveTo(int newX, int newY, int newZ) {
    auto* collitionHandler = (AnimatedEntityCollitionHandler*) _collitionHandler;

    auto* destination = new Point(newX ,newY ,newZ);

    collitionHandler->correctDestination(destination);

    collitionHandler->moveAllCollitionBoxesKeepingRelativeDistancesTo(destination);
    setPosition(destination->x,destination->y,destination->z);

    //cout<<"position: "<<"x: "<<destination->getX<<", y: "<<destination->getY<<", z: "<<destination->getZ<<endl;

    delete(destination);
}

Position::~Position() {
    delete (point);
}
