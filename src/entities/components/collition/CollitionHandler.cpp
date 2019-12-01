//
// Created by axel on 25/11/19.
//

#include "CollitionHandler.h"

bool CollitionHandler::anyCollitions() {
    return _collitionManager->anyBlockingCollitionsWith(_blockingCollitionBox);
}

void CollitionHandler::moveCollitionBoxes(Position* position) {

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

void CollitionHandler::dragToRight(int amount) {

    for (auto collitionBox: *_collitionBoxes){
        collitionBox->x += amount;
    }
}

void CollitionHandler::setOwner(Entity *owner) {

    for (auto collitionBox : *_collitionBoxes){
        collitionBox->setOwner(owner);
    }
}
