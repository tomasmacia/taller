//
// Created by axel on 25/11/19.
//

#include "CollitionManager.h"

CollitionManager::CollitionManager() {
    
    _collitionBoxes = new list<CollitionBox*>();
    _blockingCollitionBoxes = new list<BlockingCollitionBox*>();
    _nonBlockingCollitionBoxes = new list<NonBlockingCollitionBox*>();
    _characterCollitionBoxes = new list<CharacterCollitionBox*>();
    _nonCharacterCollitionBoxes = new list<NonCharacterCollitionBox*>();
}

NonCharacterCollitionBox *CollitionManager::addBlockingCollitionBox(int x, int y, int z, int w, int h, int d, Entity* owner) {

    auto* newCollitionBox = new NonCharacterCollitionBox(x,y,z,w,h,d,newID,owner);
    _nonCharacterCollitionBoxes->push_back(newCollitionBox);
    _blockingCollitionBoxes->push_back(newCollitionBox);
    _collitionBoxes->push_back(newCollitionBox);
    newID++;
    return newCollitionBox;

}

CharacterCollitionBox *CollitionManager::addCharacterCollitionBox(int x, int y, int z, int w, int h, int d, Character *owner) {

    auto* newCollitionBox = new CharacterCollitionBox(x,y,z,w,h,d,newID,owner);
    _characterCollitionBoxes->push_back(newCollitionBox);
    _blockingCollitionBoxes->push_back(newCollitionBox);
    _collitionBoxes->push_back(newCollitionBox);
    newID++;
    return newCollitionBox;
}

NonBlockingCollitionBox *CollitionManager::addNonBlockingCollitionBox(int x, int y, int z, int w, int h, int d, Entity *owner) {

    auto* newCollitionBox = new NonBlockingCollitionBox(x,y,z,w,h,d,newID,owner);
    _nonBlockingCollitionBoxes->push_back(newCollitionBox);
    _collitionBoxes->push_back(newCollitionBox);
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
    for (auto collitionBox: *_collitionBoxes){
        delete(collitionBox);
    }
    _collitionBoxes->clear();
    delete(_collitionBoxes);

    _blockingCollitionBoxes->clear();
    delete(_blockingCollitionBoxes);

    _nonBlockingCollitionBoxes->clear();
    delete(_nonBlockingCollitionBoxes);

    _characterCollitionBoxes->clear();
    delete(_characterCollitionBoxes);

    _nonCharacterCollitionBoxes->clear();
    delete(_nonCharacterCollitionBoxes);
}
