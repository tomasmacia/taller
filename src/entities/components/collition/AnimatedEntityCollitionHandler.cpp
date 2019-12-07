//
// Created by axel on 25/11/19.
//
#include <iostream>
#include "AnimatedEntityCollitionHandler.h"

AnimatedEntityCollitionHandler::AnimatedEntityCollitionHandler(CollitionManager *collitionManager,
                                                               CollitionBox *punchBox, CollitionBox *kickBox,
                                                               CollitionBox *collitionBox, CollitionBox *pickBox)


                                                               :CollitionHandler(collitionManager){
    _blockingCollitionBox = collitionBox;
    _punchBox = punchBox;
    _kickBox = kickBox;
    _pickBox = pickBox;

    addCollitionBox(_blockingCollitionBox);
    addCollitionBox(_punchBox);
    addCollitionBox(_kickBox);
    addCollitionBox(_pickBox);
}

list<Entity *> *AnimatedEntityCollitionHandler::getAllPunchableWithinPunchingRange() {

    auto* punchables = new list<Entity*>();
    auto* boxes = _collitionManager->getListOfHittedCollitionBox(_punchBox);

    for (auto colitionBox : *boxes){
        punchables->push_back(colitionBox->getOwner());
    }

    return punchables;
}

list<Entity*>* AnimatedEntityCollitionHandler::getAllKickableWithinKickingRange() {

    auto* kickeables = new list<Entity*>();
    auto* boxes = _collitionManager->getListOfHittedCollitionBox(_kickBox);

    for (auto colitionBox : *boxes){
        kickeables->push_back(colitionBox->getOwner());
    }

    return kickeables;
}

Entity *AnimatedEntityCollitionHandler::getClosestPickeableWithinPickingRange() {
    return _collitionManager->getFirstPickedCollitionBox(_pickBox)->getOwner();
}

void AnimatedEntityCollitionHandler::moveAllCollitionBoxesKeepingRelativeDistancesTo(Point *destination) {

    int diffX = destination->x - _blockingCollitionBox->getX();
    int diffY = destination->y - _blockingCollitionBox->getY();
    int diffZ = destination->z - _blockingCollitionBox->getZ();

    for (auto collitionBox : *_collitionBoxes){
        collitionBox->moveAllCornersBy(diffX,diffY,diffZ);
    }
}

void AnimatedEntityCollitionHandler::correctDestination(Point *destination) {

    moveTowardsDestinationAndCorrect(destination);
}

void AnimatedEntityCollitionHandler::moveTowardsDestinationAndCorrect(Point *destination) {

    int counter = 0;
    while (_blockingCollitionBox->notArrivedAt(destination) && counter <= TRIES){

        _blockingCollitionBox->moveOneUnitInTheDirectionOf(destination);

        list<CollitionBox*>* collitions = _collitionManager->getCollitionsWith(_blockingCollitionBox);

        if (!collitions->empty()){
            _blockingCollitionBox->restorePreviousPosition();
            correctDestinationUsing(collitions->front(), destination);
        }

        collitions->clear();
        delete(collitions);
        counter++;
    }
    counter = 0;
}

void AnimatedEntityCollitionHandler::correctDestinationUsing(CollitionBox *collitionBox, Point *destination) {

    int prevX = destination->x;
    int prevY = destination->y;
    int prevZ = destination->z;

    int currentX = _blockingCollitionBox->getX();
    int currentY = _blockingCollitionBox->getY();
    int currentZ = _blockingCollitionBox->getZ();

    destination->x = prevX;
    destination->y = currentY;
    destination->z = currentZ;

    if (collitionBox->hasInsideItsVolume(destination)){

        destination->x = currentX;
        destination->y = prevY;
        destination->z = currentZ;

        if (collitionBox->hasInsideItsVolume(destination)){

            destination->x = currentX;
            destination->y = currentY;
            destination->z = prevZ;
        }
    }
}