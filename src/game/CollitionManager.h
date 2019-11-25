//
// Created by axel on 25/11/19.
//

#ifndef GAME_COLLITIONMANAGER_H
#define GAME_COLLITIONMANAGER_H

#include <list>
#include "../entities/components/collition/CollitionBox.h"
#include "../entities/Character.h"
using namespace std;

class CollitionManager {

public:
    CollitionManager();
    ~CollitionManager();

    CollitionBox* addNewCollitionBox(int x, int y, int z, int w, int h, int d, Character* owner);
    bool anyCollitionsWith(CollitionBox* queryCollitionBox);

private:
    list<CollitionBox*>* _collitionBoxes = nullptr;
    int newID = 0;
};


#endif //GAME_COLLITIONMANAGER_H
