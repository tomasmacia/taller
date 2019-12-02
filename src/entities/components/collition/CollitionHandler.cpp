//
// Created by axel on 25/11/19.
//

#include "CollitionHandler.h"

CollitionHandler::CollitionHandler(CollitionManager* collitionManager) {

    _collitionBoxes = new list<CollitionBox*>();

    _collitionManager = collitionManager;
}

void CollitionHandler::dragToRight(int amount) {

    for (auto collitionBox: *_collitionBoxes){
        collitionBox->dragToRight(amount);
    }
}

void CollitionHandler::setOwnerToAllCollitionBox(Entity* owner) {

    for (auto b : *_collitionBoxes){
        b->setOwner(owner);
    }
}

CollitionHandler::~CollitionHandler(){
    for (auto collitionBox : *_collitionBoxes){
        _collitionManager->untrack(collitionBox);
        delete(collitionBox);
    }
    _collitionBoxes->clear();
    delete(_collitionBoxes);
}