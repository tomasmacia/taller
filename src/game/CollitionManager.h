//
// Created by axel on 25/11/19.
//

#ifndef GAME_COLLITIONMANAGER_H
#define GAME_COLLITIONMANAGER_H

#include <list>
#include "../entities/components/collition/CollitionBox.h"
#include "../entities/Character.h"
#include "../entities/components/Point.h"

using namespace std;

class CollitionManager {

public:
    CollitionManager();
    ~CollitionManager();

    void prepareForNextLevel();
    void untrack(CollitionBox* collitionBox);

    list<CollitionBox*>* getListOfHittedCollitionBox(CollitionBox* query);
    CollitionBox* getFirstPickedCollitionBox(CollitionBox* query);

    CollitionBox* addCharacterBlockingCollitionBox(int x, int y, int z, int w, int h, int d);
    CollitionBox* addEnemyBlockingCollitionBox(int x, int y, int z, int w, int h, int d);
    CollitionBox* addBackgroundBlockingCollitionBox(int x, int y, int z, int w, int h, int d);
    CollitionBox* addKnifeBlockingCollitionBox(int x, int y, int z, int w, int h, int d);
    CollitionBox* addTubeBlockingCollitionBox(int x, int y, int z, int w, int h, int d);
    CollitionBox* addBoxBlockingCollitionBox(int x, int y, int z, int w, int h, int d);
    CollitionBox* addBarrelBlockingCollitionBox(int x, int y, int z, int w, int h, int d);
    CollitionBox* addScreenBlockingCollitionBox(int x, int y, int z, int w, int h, int d);

    bool anyBlockingCollitionsWith(CollitionBox* queryCollitionBox, Point* corrected);

private:
    void clearNonLevelPersistentCollitionBoxes();

    list<CollitionBox*>* _blockingCollitionBoxes = nullptr;
    list<CollitionBox*> _nonLevelPersistentCollitionBoxes = nullptr;
    list<CollitionBox*>* _weaponCollitionBoxes = nullptr;
    list<CollitionBox*>* _characterCollitionBoxes = nullptr;
    int newID = 0;
};


#endif //GAME_COLLITIONMANAGER_H
