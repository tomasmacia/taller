//
// Created by axel on 25/11/19.
//
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

list<PhysicalEntity*> *AnimatedEntityCollitionHandler::getAllPunchableWithinPunchingRange() {

    auto* punchables = new list<PhysicalEntity*>();
    auto* boxes = _collitionManager->getListOfHittedCollitionBox(_punchBox);

    for (auto colitionBox : *boxes){
        punchables->push_back((PhysicalEntity*) colitionBox->getOwner());
    }

    boxes->clear();
    delete(boxes);

    return punchables;
}

list<PhysicalEntity*>* AnimatedEntityCollitionHandler::getAllKickableWithinKickingRange() {

    auto* kickeables = new list<PhysicalEntity*>();
    auto* boxes = _collitionManager->getListOfHittedCollitionBox(_kickBox);

    for (auto colitionBox : *boxes){
        kickeables->push_back((PhysicalEntity*) colitionBox->getOwner());
    }

    boxes->clear();
    delete(boxes);

    return kickeables;
}

PhysicalEntity *AnimatedEntityCollitionHandler::getClosestPickeableWithinPickingRange() {

    CollitionBox* pickeableBox = _collitionManager->getFirstPickedCollitionBox(_pickBox);

    if (pickeableBox != nullptr){
        return (PhysicalEntity*) pickeableBox->getOwner();
    }
    else{
        return nullptr;
    }
}

void AnimatedEntityCollitionHandler::moveAllCollitionBoxesKeepingRelativeDistancesTo(Point *destination) {

    for (auto collitionBox : *_collitionBoxes){
        collitionBox->setAt(destination->x,destination->y,destination->z);
    }
}

void AnimatedEntityCollitionHandler::correctDestination(Point *destination) {
    moveTowardsDestinationAndCorrect(destination);
}

void AnimatedEntityCollitionHandler::moveTowardsDestinationAndCorrect(Point *destination) {

    bool startOfTheCorrection = true;
    while (!_blockingCollitionBox->arrived() || startOfTheCorrection){
        startOfTheCorrection = false;
        //_blockingCollitionBox->clearDiscardedMoves();

        _blockingCollitionBox->moveOneUnitInTheDirectionOf(destination);
        //_blockingCollitionBox->discardTheOpositeOfLastMoveAsCandidate();

        if (_collitionManager->anyBlockingCollitionsWith(_blockingCollitionBox)){
            _blockingCollitionBox->restorePreviousPosition();
            _blockingCollitionBox->discardLastMoveAsCandidate();
        }
    }
    destination->setAt(_blockingCollitionBox->getCenter());
    _blockingCollitionBox->clearDiscardedMoves();
}

void AnimatedEntityCollitionHandler::setDisconected() {

    for (auto collitionBox : *_collitionBoxes){
        _collitionManager->ignoreBlockingCollitionBox(collitionBox->getID());
    }
}

void AnimatedEntityCollitionHandler::setConnected() {

    for (auto collitionBox : *_collitionBoxes){
        _collitionManager->stopIgnoringBlockingCollitionBox(collitionBox->getID());
    }
}
