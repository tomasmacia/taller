//
// Created by axel on 25/11/19.
//
#include "AnimatedEntityCollitionHandler.h"

AnimatedEntityCollitionHandler::AnimatedEntityCollitionHandler(CollitionManager *collitionManager,
                                                               CollitionBox *punchBox, CollitionBox *kickBox,
                                                               CollitionBox *collitionBox, CollitionBox *pickBox,
                                                               State *state)

                                                               :CollitionHandler(collitionManager){
    _state = state;
    _punchBox = punchBox;
    _kickBox = kickBox;
    _pickBox = pickBox;

    addBlockingCollitionBox(collitionBox);
    addNonBlockingCollitionBox(punchBox);
    addNonBlockingCollitionBox(kickBox);
    addNonBlockingCollitionBox(pickBox);
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
