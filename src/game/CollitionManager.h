//
// Created by axel on 25/11/19.
//

#ifndef GAME_COLLITIONMANAGER_H
#define GAME_COLLITIONMANAGER_H

#include <list>
#include "../entities/components/collition/collitionBoxHierarchy/CollitionBox.h"
#include "../entities/components/collition/collitionBoxHierarchy/NonBlockingCollitionBox.h"
#include "../entities/components/collition/collitionBoxHierarchy/BlockingCollitionBox.h"
#include "../entities/components/collition/collitionBoxHierarchy/CharacterCollitionBox.h"
#include "../entities/components/collition/collitionBoxHierarchy/NonCharacterCollitionBox.h"
#include "../entities/Character.h"

using namespace std;

class CollitionManager {

public:
    CollitionManager();
    ~CollitionManager();

    NonCharacterCollitionBox* addBlockingCollitionBox(int x, int y, int z, int w, int h, int d, Entity* owner);
    CharacterCollitionBox* addCharacterCollitionBox(int x, int y, int z, int w, int h, int d, Character* owner);
    NonBlockingCollitionBox* addNonBlockingCollitionBox(int x, int y, int z, int w, int h, int d, Entity* owner);
    bool anyBlockingCollitionsWith(CollitionBox* queryCollitionBox);

private:
    list<NonCharacterCollitionBox*>* _nonCharacterCollitionBoxes = nullptr;
    list<CharacterCollitionBox*>* _characterCollitionBoxes = nullptr;
    list<NonBlockingCollitionBox*>* _nonBlockingCollitionBoxes = nullptr;
    list<BlockingCollitionBox*>* _blockingCollitionBoxes = nullptr;
    list<CollitionBox*>* _collitionBoxes = nullptr;
    int newID = 0;
};


#endif //GAME_COLLITIONMANAGER_H
