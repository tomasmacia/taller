//
// Created by axel on 25/11/19.
//
#include <list>
#include "AnimatedEntityCollitionHandler.h"

AnimatedEntityCollitionHandler::AnimatedEntityCollitionHandler(CollitionBox* punchBox, CollitionBox* kickBox, CollitionBox* collitionBox,
                                                               CollitionManager* collitionManager, State* state) {

    _state = state;

    _collitionManager = collitionManager;

    _collitionBoxes = new list<CollitionBox*>();

    _blockingCollitionBox = collitionBox;
    _punchBox = punchBox;
    _kickBox = kickBox;

    _collitionBoxes->push_back(_blockingCollitionBox);
    _collitionBoxes->push_back(_punchBox);
    _collitionBoxes->push_back(_kickBox);
    _collitionBoxes->push_back(_pickBox);
}

list<Entity *> *AnimatedEntityCollitionHandler::getAllPunchableWithinPunchingRange() {

    auto* punchables = new list<Entity*>();
    auto* boxes = _collitionManager->getListOfHittedCollitionBox(_punchBox);

    for (auto colitionBox : *boxes){
        punchables->push_back(colitionBox->owner);
    }

    return punchables;
}

list<Entity*>* AnimatedEntityCollitionHandler::getAllKickableWithinKickingRange() {

    auto* kickeables = new list<Entity*>();
    auto* boxes = _collitionManager->getListOfHittedCollitionBox(_kickBox);

    for (auto colitionBox : *boxes){
        kickeables->push_back(colitionBox->owner);
    }

    return kickeables;
}

Entity *AnimatedEntityCollitionHandler::getClosestPickeableWithinPickingRange() {
    return _collitionManager->getFirstPickedCollitionBox(_pickBox)->owner;
}

AnimatedEntityCollitionHandler::~AnimatedEntityCollitionHandler(){

    for (auto collitionBox : _collitionBoxes){
        delete(collitionBox);
    }
    _collitionBoxes->clear();
    delete(_collitionBoxes);
}
