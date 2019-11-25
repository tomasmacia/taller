//
// Created by axel on 25/11/19.
//

#include "CollitionManager.h"

CollitionManager::CollitionManager() {
    _collitionBoxes = new list<CollitionBox*>();
}

CollitionBox *CollitionManager::addNewCollitionBox(int x, int y, int z, int w, int h, int d, Character* owner) {
    auto* newCollitionBox = new CollitionBox(x,y,z,w,h,d,newID,owner);
    newID++;
    return newCollitionBox;
}

bool CollitionManager::anyCollitionsWith(CollitionBox *queryCollitionBox) {

    for (auto* collitionBox: *_collitionBoxes){
        if (collitionBox->id != queryCollitionBox->id){
            if (collitionBox->intersectsWith(queryCollitionBox)){
                return true;
            }
        }
    }
    return false;
}

CollitionManager::~CollitionManager(){
    for (auto collitionBox: *_collitionBoxes){
        delete(collitionBox);
    }
    _collitionBoxes->clear();
    delete(_collitionBoxes);
}
