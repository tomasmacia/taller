//
// Created by axel on 25/11/19.
//

#include "CollitionManager.h"
#include "../entities/entityHierarchy/Entity.h"

CollitionManager::CollitionManager() {

    _blockingCollitionBoxes = new list<CollitionBox*>();
}

CollitionBox *CollitionManager::createCharacterBlockingCollitionBox(int x, int y, int z, int w, int h, int d) {

    auto* newCollitionBox = new CollitionBox(x,y,z,w,h,d,newID);
    _blockingCollitionBoxes->push_back(newCollitionBox);
    newID++;
    return newCollitionBox;
}

CollitionBox *CollitionManager::createEnemyBlockingCollitionBox(int x, int y, int z, int w, int h, int d) {

    auto* newCollitionBox = new CollitionBox(x,y,z,w,h,d,newID);
    _blockingCollitionBoxes->push_back(newCollitionBox);
    _nonLevelPersistentCollitionBoxes->push_back(newCollitionBox);
    newID++;
    return newCollitionBox;
}

CollitionBox *CollitionManager::createBackgroundBlockingCollitionBox(int x, int y, int z, int w, int h, int d) {

    auto* newCollitionBox = new CollitionBox(x,y,z,w,h,d,newID);
    _blockingCollitionBoxes->push_back(newCollitionBox);
    _nonLevelPersistentCollitionBoxes->push_back(newCollitionBox);
    newID++;
    return newCollitionBox;
}

CollitionBox *CollitionManager::createKnifeBlockingCollitionBox(int x, int y, int z, int w, int h, int d) {

    auto* newCollitionBox = new CollitionBox(x,y,z,w,h,d,newID);
    _blockingCollitionBoxes->push_back(newCollitionBox);
    _weaponCollitionBoxes->push_back(newCollitionBox);
    _nonLevelPersistentCollitionBoxes->push_back(newCollitionBox);
    newID++;
    return newCollitionBox;
}

CollitionBox *CollitionManager::createTubeBlockingCollitionBox(int x, int y, int z, int w, int h, int d) {

    auto* newCollitionBox = new CollitionBox(x,y,z,w,h,d,newID);
    _blockingCollitionBoxes->push_back(newCollitionBox);
    _weaponCollitionBoxes->push_back(newCollitionBox);
    _nonLevelPersistentCollitionBoxes->push_back(newCollitionBox);
    newID++;
    return newCollitionBox;
}

CollitionBox *CollitionManager::createBoxBlockingCollitionBox(int x, int y, int z, int w, int h, int d) {

    auto* newCollitionBox = new CollitionBox(x,y,z,w,h,d,newID);
    _blockingCollitionBoxes->push_back(newCollitionBox);
    _nonLevelPersistentCollitionBoxes->push_back(newCollitionBox);
    newID++;
    return newCollitionBox;
}

CollitionBox *CollitionManager::createBarrelBlockingCollitionBox(int x, int y, int z, int w, int h, int d) {

    auto* newCollitionBox = new CollitionBox(x,y,z,w,h,d,newID);
    _blockingCollitionBoxes->push_back(newCollitionBox);
    _nonLevelPersistentCollitionBoxes->push_back(newCollitionBox);
    newID++;
    return newCollitionBox;
}

CollitionBox *CollitionManager::createScreenBlockingCollitionBox(int x, int y, int z, int w, int h, int d) {

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

bool CollitionManager::anyBlockingCollitionsWith(CollitionBox *queryCollitionBox) {

    for (auto* collitionBox: *_blockingCollitionBoxes){
        if (collitionBox->getID() != queryCollitionBox->getID()){
            if (collitionBox->intersectsWith(queryCollitionBox)){
                return true;
            }
        }
    }
    return false;
}

list<CollitionBox*>* CollitionManager::getCollitionsWith(CollitionBox *query) {

    auto collitions = new list<CollitionBox*>();

    for (auto collitionBox : *_blockingCollitionBoxes){
        if (collitionBox->getID() != query->getID() ){
            if (collitionBox->intersectsWith(query)){
                if (!((query->getOwner()->isScreen() && collitionBox->getOwner()->isEnemy())
                 || (query->getOwner()->isScreen() && collitionBox->getOwner()->isFinalBoss())
                 || (query->getOwner()->isEnemy() && collitionBox->getOwner()->isScreen())
                 || (query->getOwner()->isFinalBoss() && collitionBox->getOwner()->isScreen()))){

                    collitions->push_back(collitionBox);
                }
            }
        }
    }
    return collitions;
}

void CollitionManager::prepareForNextLevel() {
    clearNonLevelPersistentCollitionBoxes();
}

void CollitionManager::clearNonLevelPersistentCollitionBoxes(){
    _nonLevelPersistentCollitionBoxes->clear();
    _weaponCollitionBoxes->clear();
}

void CollitionManager::untrack(CollitionBox* collitionBox) {
    _blockingCollitionBoxes->remove(collitionBox);
    _nonLevelPersistentCollitionBoxes->remove(collitionBox);
    _weaponCollitionBoxes->remove(collitionBox);
    _characterCollitionBoxes->remove(collitionBox);
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
