//
// Created by axel on 25/11/19.
//

#include "CollitionManager.h"

CollitionManager::CollitionManager() {

    _blockingCollitionBoxes = new list<CollitionBox*>();
}

CollitionBox *CollitionManager::addCharacterBlockingCollitionBox(int x, int y, int z, int w, int h, int d) {

    auto* newCollitionBox = new CollitionBox(x,y,z,w,h,d,newID);
    _blockingCollitionBoxes->push_back(newCollitionBox);
    newID++;
    return newCollitionBox;
}

CollitionBox *CollitionManager::addEnemyBlockingCollitionBox(int x, int y, int z, int w, int h, int d) {

    auto* newCollitionBox = new CollitionBox(x,y,z,w,h,d,newID);
    _blockingCollitionBoxes->push_back(newCollitionBox);
    _nonLevelPersistentCollitionBoxes->push_back(newCollitionBox);
    newID++;
    return newCollitionBox;
}

CollitionBox *CollitionManager::addBackgroundBlockingCollitionBox(int x, int y, int z, int w, int h, int d) {

    auto* newCollitionBox = new CollitionBox(x,y,z,w,h,d,newID);
    _blockingCollitionBoxes->push_back(newCollitionBox);
    _nonLevelPersistentCollitionBoxes->push_back(newCollitionBox);
    newID++;
    return newCollitionBox;
}

CollitionBox *CollitionManager::addKnifeBlockingCollitionBox(int x, int y, int z, int w, int h, int d) {

    auto* newCollitionBox = new CollitionBox(x,y,z,w,h,d,newID);
    _blockingCollitionBoxes->push_back(newCollitionBox);
    _weaponCollitionBoxes->push_back(newCollitionBox);
    _nonLevelPersistentCollitionBoxes->push_back(newCollitionBox);
    newID++;
    return newCollitionBox;
}

CollitionBox *CollitionManager::addTubeBlockingCollitionBox(int x, int y, int z, int w, int h, int d) {

    auto* newCollitionBox = new CollitionBox(x,y,z,w,h,d,newID);
    _blockingCollitionBoxes->push_back(newCollitionBox);
    _weaponCollitionBoxes->push_back(newCollitionBox);
    _nonLevelPersistentCollitionBoxes->push_back(newCollitionBox);
    newID++;
    return newCollitionBox;
}

CollitionBox *CollitionManager::addBoxBlockingCollitionBox(int x, int y, int z, int w, int h, int d) {

    auto* newCollitionBox = new CollitionBox(x,y,z,w,h,d,newID);
    _blockingCollitionBoxes->push_back(newCollitionBox);
    _nonLevelPersistentCollitionBoxes->push_back(newCollitionBox);
    newID++;
    return newCollitionBox;
}

CollitionBox *CollitionManager::addBarrelBlockingCollitionBox(int x, int y, int z, int w, int h, int d) {

    auto* newCollitionBox = new CollitionBox(x,y,z,w,h,d,newID);
    _blockingCollitionBoxes->push_back(newCollitionBox);
    _nonLevelPersistentCollitionBoxes->push_back(newCollitionBox);
    newID++;
    return newCollitionBox;
}

list<CollitionBox *> *CollitionManager::getListOfHittedCollitionBox(CollitionBox *query) {
    return nullptr;
}

CollitionBox *CollitionManager::getFirstPickedCollitionBox(CollitionBox *query) {
    return nullptr;
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

void CollitionManager::clearNonLevelPersistentCollitionBoxes(){
    for (auto collitionBox: *_nonLevelPersistentCollitionBoxes){
        delete(collitionBox);
    }
    _nonLevelPersistentCollitionBoxes->clear();
    _weaponCollitionBoxes->clear();
}

CollitionManager::~CollitionManager(){
    for (auto collitionBox: *_blockingCollitionBoxes){
        delete(collitionBox);
    }
    _blockingCollitionBoxes->clear();
    delete(_blockingCollitionBoxes);
    _characterCollitionBoxes->clear();
    delete(_characterCollitionBoxes);
    _weaponCollitionBoxes->clear();
    delete(_weaponCollitionBoxes);
    _nonLevelPersistentCollitionBoxes->clear();
    delete(_nonLevelPersistentCollitionBoxes);
}

void CollitionManager::prepareForNextLevel() {
    clearNonLevelPersistentCollitionBoxes();
}
