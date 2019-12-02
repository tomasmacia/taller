//
// Created by axel on 25/11/19.
//

#include "CollitionHandler.h"

CollitionHandler::CollitionHandler(CollitionManager* collitionManager) {

    _corrected = new Point(0, 0, 0);

    _blockingCollitionBoxes = new list<CollitionBox*>();
    _collitionBoxes = new list<CollitionBox*>();

    _collitionManager = collitionManager;
}

bool CollitionHandler::anyCollitions() {

    for(auto b : *_blockingCollitionBoxes){
        if (_collitionManager->anyBlockingCollitionsWith(b, _corrected)){
            return true;
        }
    }
    return false;
}

void CollitionHandler::addBlockingCollitionBox(CollitionBox *collitionBox) {
    _blockingCollitionBoxes->push_back(collitionBox);
    _collitionBoxes->push_back(collitionBox);
}

void CollitionHandler::addNonBlockingCollitionBox(CollitionBox *collitionBox) {
    _collitionBoxes->push_back(collitionBox);

}

CollitionBox *CollitionHandler::addBlockingCollitionBox(int x, int y, int z, int w, int h, int d) {

    auto* newCollitionBox = _collitionManager->addScreenBlockingCollitionBox(x,y,z,w,h,d);
    _blockingCollitionBoxes->push_back(newCollitionBox);
    _collitionBoxes->push_back(newCollitionBox);
}

CollitionBox *CollitionHandler::addNonBlockingCollitionBox(int x, int y, int z, int w, int h, int d) {

    auto* newCollitionBox = _collitionManager->addScreenBlockingCollitionBox(x,y,z,w,h,d);
    _collitionBoxes->push_back(newCollitionBox);
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

void CollitionHandler::setOwnerToAllCollitionBox(Entity* owner) {

    for (auto b : *_collitionBoxes){
        b->setOwner(owner);
    }
}

CollitionHandler::~CollitionHandler(){

    for (auto collitionBox : *_blockingCollitionBoxes){
        _collitionManager->untrack(collitionBox);
    }

    for (auto collitionBox : *_collitionBoxes){
        delete(collitionBox);
    }
    _blockingCollitionBoxes->clear();
    delete(_blockingCollitionBoxes);
    _collitionBoxes->clear();
    delete(_collitionBoxes);
    delete(_corrected);

}