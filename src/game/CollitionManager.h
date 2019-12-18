//
// Created by axel on 25/11/19.
//

#ifndef GAME_COLLITIONMANAGER_H
#define GAME_COLLITIONMANAGER_H

#include <list>
#include "../entities/components/Point.h"
#include "../entities/components/collition/CollitionBox.h"

using namespace std;

class Character;
class CollitionManager {

public:
    CollitionManager();
    ~CollitionManager();

    void prepareForNextLevel();
    void untrack(CollitionBox* collitionBox);

    list<CollitionBox*>* getListOfHittedCollitionBox(CollitionBox* query);
    list<CollitionBox *> *getListOfHittedNonCharacterCollitionBox(CollitionBox *query);
    list<CollitionBox *> *getListOfHittedCharacterCollitionBox(CollitionBox *query);
    CollitionBox* getFirstPickedCollitionBox(CollitionBox* query);

    CollitionBox* createCharacterBlockingCollitionBox(int x, int y, int z, int w, int h, int d, bool visual);
    CollitionBox* createEnemyBlockingCollitionBox(int x, int y, int z, int w, int h, int d, bool visual);
    CollitionBox* createBackgroundBlockingCollitionBox(int x, int y, int z, int w, int h, int d, bool visual);
    CollitionBox* createKnifeBlockingCollitionBox(int x, int y, int z, int w, int h, int d, bool visual);
    CollitionBox* createTubeBlockingCollitionBox(int x, int y, int z, int w, int h, int d, bool visual);
    CollitionBox* createBoxBlockingCollitionBox(int x, int y, int z, int w, int h, int d, bool visual);
    CollitionBox* createBarrelBlockingCollitionBox(int x, int y, int z, int w, int h, int d, bool visual);
    CollitionBox* createScreenBlockingCollitionBox(int x, int y, int z, int w, int h, int d, bool visual);

    bool anyBlockingCollitionsInWith(list<CollitionBox*>* collitionBoxes, CollitionBox *queryCollitionBox);
    bool anyBlockingCollitionsWith(CollitionBox* queryCollitionBox);
    list<CollitionBox*>* getCollitionsInWith(list<CollitionBox*>* toCheck, CollitionBox* query);
    void ignoreBlockingCollitionBox(int id);
    void stopIgnoringBlockingCollitionBox(int id);
    void setLeftScreenBlockingCollitionBox(CollitionBox *pBox);

private:
    CollitionBox* findCollitionBoxByID(int id);
    void clearNonLevelPersistentCollitionBoxes();

    list<CollitionBox*>* _blockingCollitionBoxes = nullptr;
    list<CollitionBox*>* _enemiesCollitionBoxes = nullptr;
    list<CollitionBox*>* _utilitiesCollitionBoxes = nullptr;
    list<CollitionBox*>* _nonLevelPersistentCollitionBoxes = nullptr;
    list<CollitionBox*>* _weaponCollitionBoxes = nullptr;
    list<CollitionBox*>* _characterCollitionBoxes = nullptr;
    list<CollitionBox*>* _ignoredCollitionBoxes = nullptr;
    CollitionBox* leftScreen0BlockingCollitionBox = nullptr;

    int newID = 0;
};


#endif //GAME_COLLITIONMANAGER_H
