//
// Created by axel on 25/11/19.
//

#include "CollitionHandler.h"

bool CollitionHandler::noCollitionsIn(int newX, int newY, int newZ) {

    _collitionBox->tryPos(newX, newY, newZ);
    bool result = !_collitionManager->anyCollitionsWith(_collitionBox);
    _collitionBox->resetPos();

    return result;
}

void CollitionHandler::moveCollitionBoxes(Position* position, State* state) {

    int diffX;
    int diffY;
    int diffZ;

    for (auto collitionBox: *_collitionBoxes){

        diffX = position->getX() - collitionBox->x;
        diffY = position->getY() - collitionBox->y;
        diffZ = position->getZ() - collitionBox->z;

        collitionBox->x += diffX;
        collitionBox->y += diffY;
        collitionBox->z += diffZ;
    }
}