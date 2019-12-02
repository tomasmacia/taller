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

CollitionBox *CollitionManager::addScreenBlockingCollitionBox(int x, int y, int z, int w, int h, int d) {

    auto* newCollitionBox = new CollitionBox(x,y,z,w,h,d,newID);
    _blockingCollitionBoxes->push_back(newCollitionBox);
    newID++;
    return newCollitionBox;
}

list<CollitionBox *> *CollitionManager::getListOfHittedCollitionBox(CollitionBox *query) {

    auto hitted = new list<CollitionBox*>();

    for (auto* collitionBox: *_blockingCollitionBoxes){
        if (collitionBox->getID() != query->getID()){
            if (collitionBox->intersectsWith(query)){
                hitted->push_back(collitionBox);
            }
        }
    }
    return hitted;
}

CollitionBox *CollitionManager::getFirstPickedCollitionBox(CollitionBox *query) {

    for (auto* collitionBox: *_blockingCollitionBoxes){
        if (collitionBox->getID() != query->getID()){
            if (collitionBox->intersectsWith(query)){
                return collitionBox;
            }
        }
    }
}

bool CollitionManager::anyBlockingCollitionsWith(CollitionBox *queryCollitionBox, Point* corrected) {

    for (auto* collitionBox: *_blockingCollitionBoxes){
        if (collitionBox->getID() != queryCollitionBox->getID()){
            if (collitionBox->intersectsWith(queryCollitionBox, corrected)){
                return true;
            }
        }
    }
    return false;
}

void CollitionManager::prepareForNextLevel() {
    clearNonLevelPersistentCollitionBoxes();
}

void CollitionManager::clearNonLevelPersistentCollitionBoxes(){
    _nonLevelPersistentCollitionBoxes->clear();
    _weaponCollitionBoxes->clear();
}

CollitionManager::~CollitionManager(){
    _blockingCollitionBoxes->clear();
    delete(_blockingCollitionBoxes);
    _characterCollitionBoxes->clear();
    delete(_characterCollitionBoxes);
    _weaponCollitionBoxes->clear();
    delete(_weaponCollitionBoxes);
    _nonLevelPersistentCollitionBoxes->clear();
    delete(_nonLevelPersistentCollitionBoxes);
}

void CollitionManager::untrack(CollitionBox* collitionBox) {
    _blockingCollitionBoxes->remove(collitionBox);
    _nonLevelPersistentCollitionBoxes->remove(collitionBox);
    _weaponCollitionBoxes->remove(collitionBox);
    _characterCollitionBoxes->remove(collitionBox);
}
