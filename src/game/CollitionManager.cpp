//
// Created by axel on 25/11/19.
//

#include "CollitionManager.h"

CollitionManager::CollitionManager() {

    _blockingCollitionBoxes = new list<CollitionBox*>();
}

CollitionBox *CollitionManager::addBlockingCollitionBox(int x, int y, int z, int w, int h, int d, Entity *owner) {

    auto* newCollitionBox = new CollitionBox(x,y,z,w,h,d,newID,owner);
    _blockingCollitionBoxes->push_back(newCollitionBox);
    newID++;
    return newCollitionBox;
}


bool CollitionManager::anyBlockingCollitionsWith(CollitionBox *queryCollitionBox) {

    for (auto* collitionBox: *_blockingCollitionBoxes){
        if (collitionBox->id != queryCollitionBox->id){
            if (collitionBox->intersectsWith(queryCollitionBox)){
                return true;
            }
        }
    }
    return false;
}

CollitionManager::~CollitionManager(){
    for (auto collitionBox: *_blockingCollitionBoxes){
        delete(collitionBox);
    }
    _blockingCollitionBoxes->clear();
    delete(_blockingCollitionBoxes);
}
