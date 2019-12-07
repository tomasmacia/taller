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

void Position::tryToMoveTo(int newX, int newY, int newZ) {
    auto* collitionHandler = (AnimatedEntityCollitionHandler*) _collitionHandler;

    auto* destination = new Point(newX,newY,newZ);

    collitionHandler->correctDestination(destination);

    setPosition(destination->x,destination->y,destination->z);
    collitionHandler->moveAllCollitionBoxesKeepingRelativeDistancesTo(destination);

    //cout<<"position: "<<"x: "<<destination->x<<", y: "<<destination->y<<", z: "<<destination->z<<endl;

    delete(destination);
}

Position::~Position() {
    delete (point);
}