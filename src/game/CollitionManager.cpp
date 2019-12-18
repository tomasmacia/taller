//
// Created by axel on 25/11/19.
//

#include <iostream>
#include <algorithm>
#include "CollitionManager.h"
#include "../entities/entityHierarchy/Entity.h"
#include "../entities/Character.h"

CollitionManager::CollitionManager() {

    _blockingCollitionBoxes = new list<CollitionBox*>();
    _nonLevelPersistentCollitionBoxes = new list<CollitionBox*>();
    _weaponCollitionBoxes = new list<CollitionBox*>();
    _characterCollitionBoxes = new list<CollitionBox*>();
    _enemiesCollitionBoxes = new list<CollitionBox*>();
    _utilitiesCollitionBoxes = new list<CollitionBox*>();
    _ignoredCollitionBoxes = new list<CollitionBox*>();
}

CollitionBox *CollitionManager::createCharacterBlockingCollitionBox(int x, int y, int z, int w, int h, int d, bool visual) {

    auto* newCollitionBox = new CollitionBox(x,y,z,w,h,d,newID,visual);
    _blockingCollitionBoxes->push_back(newCollitionBox);
    _characterCollitionBoxes->push_back(newCollitionBox);
    newID++;
    return newCollitionBox;
}

CollitionBox *CollitionManager::createEnemyBlockingCollitionBox(int x, int y, int z, int w, int h, int d, bool visual) {

    auto* newCollitionBox = new CollitionBox(x,y,z,w,h,d,newID,visual);
    _blockingCollitionBoxes->push_back(newCollitionBox);
    _nonLevelPersistentCollitionBoxes->push_back(newCollitionBox);
    _enemiesCollitionBoxes->push_back(newCollitionBox);
    newID++;
    return newCollitionBox;
}

CollitionBox *CollitionManager::createBackgroundBlockingCollitionBox(int x, int y, int z, int w, int h, int d, bool visual) {

    auto* newCollitionBox = new CollitionBox(x,y,z,w,h,d,newID,visual);
    _blockingCollitionBoxes->push_back(newCollitionBox);
    _nonLevelPersistentCollitionBoxes->push_back(newCollitionBox);
    newID++;
    return newCollitionBox;
}

CollitionBox *CollitionManager::createKnifeBlockingCollitionBox(int x, int y, int z, int w, int h, int d, bool visual) {

    auto* newCollitionBox = new CollitionBox(x,y,z,w,h,d,newID,visual);
    _weaponCollitionBoxes->push_back(newCollitionBox);
    _nonLevelPersistentCollitionBoxes->push_back(newCollitionBox);
    newID++;
    return newCollitionBox;
}

CollitionBox *CollitionManager::createTubeBlockingCollitionBox(int x, int y, int z, int w, int h, int d, bool visual) {

    auto* newCollitionBox = new CollitionBox(x,y,z,w,h,d,newID,visual);
    _weaponCollitionBoxes->push_back(newCollitionBox);
    _nonLevelPersistentCollitionBoxes->push_back(newCollitionBox);
    newID++;
    return newCollitionBox;
}

CollitionBox *CollitionManager::createBoxBlockingCollitionBox(int x, int y, int z, int w, int h, int d, bool visual) {

    auto* newCollitionBox = new CollitionBox(x,y,z,w,h,d,newID,visual);
    _blockingCollitionBoxes->push_back(newCollitionBox);
    _nonLevelPersistentCollitionBoxes->push_back(newCollitionBox);
    _utilitiesCollitionBoxes->push_back(newCollitionBox);
    newID++;
    return newCollitionBox;
}

CollitionBox *CollitionManager::createBarrelBlockingCollitionBox(int x, int y, int z, int w, int h, int d, bool visual) {

    auto* newCollitionBox = new CollitionBox(x,y,z,w,h,d,newID,visual);
    _blockingCollitionBoxes->push_back(newCollitionBox);
    _nonLevelPersistentCollitionBoxes->push_back(newCollitionBox);
    _utilitiesCollitionBoxes->push_back(newCollitionBox);
    newID++;
    return newCollitionBox;
}

CollitionBox *CollitionManager::createScreenBlockingCollitionBox(int x, int y, int z, int w, int h, int d, bool visual) {

    auto* newCollitionBox = new CollitionBox(x,y,z,w,h,d,newID,visual);
    _blockingCollitionBoxes->push_back(newCollitionBox);
    newID++;
    return newCollitionBox;
}

list<CollitionBox *> *CollitionManager::getListOfHittedNonCharacterCollitionBox(CollitionBox *query) {
    return getListOfHittedCollitionBox(query);
}

list<CollitionBox *> *CollitionManager::getListOfHittedCharacterCollitionBox(CollitionBox *query) {

    auto hitted = new list<CollitionBox*>();

    bool isIgnored;

    for (auto* collitionBox: *_characterCollitionBoxes){

        isIgnored = (std::find(_ignoredCollitionBoxes->begin(), _ignoredCollitionBoxes->end(), collitionBox) != _ignoredCollitionBoxes->end());

        if (collitionBox->getID() != query->getID()){
            if (!isIgnored && collitionBox->intersectsWith(query)){
                hitted->push_back(collitionBox);
            }
        }
    }

    return hitted;
}

list<CollitionBox *> *CollitionManager::getListOfHittedCollitionBox(CollitionBox *query) {

    auto hitted = new list<CollitionBox*>();

    for (auto* collitionBox: *_enemiesCollitionBoxes){
        if (collitionBox->getID() != query->getID()){
            if (collitionBox->intersectsWith(query)){
                hitted->push_back(collitionBox);
            }
        }
    }

    for (auto* collitionBox: *_utilitiesCollitionBoxes){
        if (collitionBox->getID() != query->getID()){
            if (collitionBox->intersectsWith(query)){
                hitted->push_back(collitionBox);
            }
        }
    }
    return hitted;
}

CollitionBox *CollitionManager::getFirstPickedCollitionBox(CollitionBox *query) {

    for (auto* collitionBox: *_weaponCollitionBoxes){
        if (collitionBox->getID() != query->getID()){
            if (collitionBox->intersectsWith(query)){
                return collitionBox;
            }
        }
    }
    return nullptr;
}

bool CollitionManager::anyBlockingCollitionsInWith(list<CollitionBox*>* collitionBoxes, CollitionBox *queryCollitionBox) {

    for (auto* collitionBox: *collitionBoxes){
        if (collitionBox->getID() != queryCollitionBox->getID()){
            if (collitionBox->intersectsWith(queryCollitionBox)){
                //cout<<"query: "<<query->getID()<<", intersected: "<<collitionBox->getID()<<endl;
                if (!((queryCollitionBox->getOwner()->isScreen() && collitionBox->getOwner()->isEnemy())
                      || (queryCollitionBox->getOwner()->isScreen() && collitionBox->getOwner()->isFinalBoss())
                      || (queryCollitionBox->getOwner()->isEnemy() && collitionBox->getOwner()->isScreen())
                      || (queryCollitionBox->getOwner()->isFinalBoss() && collitionBox->getOwner()->isScreen()))){
                    return true;
                }
            }
        }
    }
    return false;
}

bool CollitionManager::anyBlockingCollitionsWith(CollitionBox *query) {

    bool isIgnored = (std::find(_ignoredCollitionBoxes->begin(), _ignoredCollitionBoxes->end(), query) != _ignoredCollitionBoxes->end());

    if (isIgnored){
        auto otherIgnored = getCollitionsInWith(_ignoredCollitionBoxes,query);

        for (auto ignored : *otherIgnored){
            auto player = (Character*) ignored->getOwner();
            player->drag();
        }
        delete(otherIgnored);

        return false;
    }
    else{
        return anyBlockingCollitionsInWith(_blockingCollitionBoxes,query);
    }
}

list<CollitionBox*>* CollitionManager::getCollitionsInWith(list<CollitionBox*>* toCheck, CollitionBox* query) {

    auto collitions = new list<CollitionBox*>();
    for (auto collitionBox : *toCheck){
        if (collitionBox->getID() != query->getID() ){
            if (collitionBox->intersectsWith(query)){
                //cout<<"query: "<<query->getID()<<", intersected: "<<collitionBox->getID()<<endl;
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
    _enemiesCollitionBoxes->clear();
    _utilitiesCollitionBoxes->clear();
}

void CollitionManager::untrack(CollitionBox* collitionBox) {
    _blockingCollitionBoxes->remove(collitionBox);
    _nonLevelPersistentCollitionBoxes->remove(collitionBox);
    _weaponCollitionBoxes->remove(collitionBox);
    _characterCollitionBoxes->remove(collitionBox);
    _enemiesCollitionBoxes->remove(collitionBox);
    _utilitiesCollitionBoxes->remove(collitionBox);
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
    _enemiesCollitionBoxes->clear();
    delete(_enemiesCollitionBoxes);
    _utilitiesCollitionBoxes->clear();
    delete(_utilitiesCollitionBoxes);
    _ignoredCollitionBoxes->clear();
    delete(_ignoredCollitionBoxes);
}

void CollitionManager::ignoreBlockingCollitionBox(int id) {

    auto toIgnoreCollitionBox = findCollitionBoxByID(id);

    if (toIgnoreCollitionBox != nullptr){

        _blockingCollitionBoxes->remove(toIgnoreCollitionBox);
        _ignoredCollitionBoxes->push_back(toIgnoreCollitionBox);
    }
}

CollitionBox* CollitionManager::findCollitionBoxByID(int id) {

    for (auto collitionBox : *_blockingCollitionBoxes){

        if (collitionBox->getID() == id){
            return collitionBox;
        }
    }

    for (auto collitionBox : *_ignoredCollitionBoxes){ // si no estaba en los collition box de bloqueo entonces busco en los ignorados

        if (collitionBox->getID() == id){
            return collitionBox;
        }
    }

    return nullptr;
}

void CollitionManager::stopIgnoringBlockingCollitionBox(int id) {

    auto toStopIgnoringCollitionBox = findCollitionBoxByID(id);

    if (toStopIgnoringCollitionBox != nullptr){

        _ignoredCollitionBoxes->remove(toStopIgnoringCollitionBox);
        _blockingCollitionBoxes->push_back(toStopIgnoringCollitionBox);
    }
}

void CollitionManager::setLeftScreenBlockingCollitionBox(CollitionBox *pBox) {
    leftScreen0BlockingCollitionBox = pBox;
}