//
// Created by axel on 25/11/19.
//
#include "AnimatedEntityCollitionHandler.h"

AnimatedEntityCollitionHandler::AnimatedEntityCollitionHandler(State* state, CollitionManager *collitionManager,
                                                               CollitionBox *punchBox, CollitionBox *kickBox,
                                                               CollitionBox *collitionBox, CollitionBox *pickBox)


                                                               :CollitionHandler(collitionManager){
    _state = state;

    _blockingCollitionBox = collitionBox;
    _punchBox = punchBox;
    _kickBox = kickBox;
    _pickBox = pickBox;

    addCollitionBox(_blockingCollitionBox);
    addCollitionBox(_punchBox);
    addCollitionBox(_kickBox);
    addCollitionBox(_pickBox);

    lastFacingState = _state->facingRight();
    lastAttack = state->getWeapon();
    normalPunchingWidth = _punchBox->getWidth();
}

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

void AnimatedEntityCollitionHandler::setState(State *state) {
    _state = state;
    lastFacingState = _state->facingRight();
    lastAttack = _state->getWeapon();
    normalPunchingWidth = _punchBox->getWidth();
}

list<PhysicalEntity*>* AnimatedEntityCollitionHandler::getAllPunchableWithinPunchingRange() {

    auto* punchables = new list<PhysicalEntity*>();
    list<CollitionBox*>* boxes = nullptr;

    if (_blockingCollitionBox->getOwner()->isCharacter()){

        boxes = _collitionManager->getListOfHittedCharacterCollitionBox(_punchBox);
    }
    else{
        boxes = _collitionManager->getListOfHittedCharacterCollitionBox(_punchBox);
    }

    if (boxes != nullptr){
        for (auto colitionBox : *boxes){
            punchables->push_back((PhysicalEntity*) colitionBox->getOwner());
        }
        boxes->clear();
        delete(boxes);
    }

    return punchables;
}

list<PhysicalEntity*>* AnimatedEntityCollitionHandler::getAllKickableWithinKickingRange() {

    auto* kickeables = new list<PhysicalEntity*>();
    list<CollitionBox*>* boxes = nullptr;

    if (_blockingCollitionBox->getOwner()->isCharacter()){

        boxes = _collitionManager->getListOfHittedNonCharacterCollitionBox(_kickBox);
    }
    else{
        boxes = _collitionManager->getListOfHittedCharacterCollitionBox(_kickBox);
    }

    if (boxes != nullptr){
        for (auto colitionBox : *boxes){
            kickeables->push_back((PhysicalEntity*) colitionBox->getOwner());
        }
        boxes->clear();
        delete(boxes);
    }

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

    auto delta = destination->minus(_blockingCollitionBox->getOwner()->getPos());

    /*
    for (auto collitionBox : *_collitionBoxes){
        if (collitionBox->getID() != _blockingCollitionBox->getID()){
            collitionBox->moveBy(delta);
        }
    }
     */

    _punchBox->moveBy(delta);
    _kickBox->moveBy(delta);
    _pickBox->moveBy(delta);
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

void AnimatedEntityCollitionHandler::update() {

    if (playerFliped()){
        reflectAllAttackCollitionBox();
    }

    if (attackChanged()){
        adaptPunchingBox();
    }
}

void AnimatedEntityCollitionHandler::reflectAllAttackCollitionBox() {

    _punchBox->reflectInXRespectTo(_blockingCollitionBox->getOwner()->getPos());
    _kickBox->reflectInXRespectTo(_blockingCollitionBox->getOwner()->getPos());
}

bool AnimatedEntityCollitionHandler::playerFliped() {

    if (lastFacingState != _state->facingRight()){
        lastFacingState = _state->facingRight();
        return true;
    }
    else{
        return false;
    }
}

bool AnimatedEntityCollitionHandler::attackChanged() {

    if (lastAttack != _state->getWeapon()){
        lastAttack = _state->getWeapon();
        return true;
    }
    else{
        return false;
    }
}

void AnimatedEntityCollitionHandler::adaptPunchingBox() {

    switch (lastAttack){
        case NO_WEAPON:
            _punchBox->adaptWidthToRespectTo(normalPunchingWidth, _punchBox->getOwner()->getPos());
            break;
        case KNIFE:
            _punchBox->adaptWidthToRespectTo(normalPunchingWidth * KNIFE_WIDTH_SCALE_FACTOR,_punchBox->getOwner()->getPos());
            break;
        case TUBE:
            _punchBox->adaptWidthToRespectTo(normalPunchingWidth * TUBE_WIDTH_SCALE_FACTOR,_punchBox->getOwner()->getPos());
            break;
    }
}
