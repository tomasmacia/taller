//
// Created by axel on 25/11/19.
//

#include "CollitionHandler.h"

CollitionHandler::CollitionHandler(CollitionManager* collitionManager) {

    _collitionBoxes = new list<CollitionBox*>();
    _collitionManager = collitionManager;
}

void CollitionHandler::addCollitionBox(CollitionBox *collitionBox) {

    _collitionBoxes->push_back(collitionBox);
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

void CollitionHandler::eraseCollitionBoxes() {
    for (auto collitionBox : *_collitionBoxes){
        _collitionManager->untrack(collitionBox);
        delete(collitionBox);
    }
    _collitionBoxes->clear();
}

CollitionHandler::~CollitionHandler(){
    eraseCollitionBoxes();
    delete(_collitionBoxes);
}

list<Sendable*> CollitionHandler::generateSendable() {
    list<Sendable*> sendables;
    for (auto collitionBox : *_collitionBoxes){
        if (collitionBox->isVisual()){
            sendables.push_back(collitionBox->generateSendable());
        }
    }
    return sendables;
}

void CollitionHandler::setToAllCollitionBoxScreenPosition(ScreenPosition *screenPosition) {

    for (auto collitionBox : *_collitionBoxes){
        collitionBox->setScreenPosition(screenPosition);
    }
}

void CollitionHandler::setAllCollitionBoxCenterAt(int x, int y, int z) {
    for (auto collitionBox: *_collitionBoxes){
        collitionBox->setAt(x,y,z);
    }
}
