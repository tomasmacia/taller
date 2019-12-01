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

    CollitionBox* addBlockingCollitionBox(int x, int y, int z, int w, int h, int d);
    bool anyBlockingCollitionsWith(CollitionBox* queryCollitionBox);

private:
    list<CollitionBox*>* _blockingCollitionBoxes = nullptr;
    int newID = 0;
};


#endif //GAME_COLLITIONMANAGER_H
