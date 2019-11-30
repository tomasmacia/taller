//
// Created by axel on 25/11/19.
//

#ifndef GAME_COLLITIONHANDLER_H
#define GAME_COLLITIONHANDLER_H


#include "../Position.h"
#include "collitionBoxHierarchy/CollitionBox.h"
#include "../State.h"
#include "../../../game/CollitionManager.h"
using namespace std;

class CollitionHandler {

public:
    void dragToRight(int amount);
    bool anyCollitions();
    void moveCollitionBoxes(Position* position);

protected:
    State* _state = nullptr;

    BlockingCollitionBox* _blockingCollitionBox = nullptr;
    CollitionManager* _collitionManager = nullptr;

    list<CollitionBox*>* _collitionBoxes = nullptr;

};


#endif //GAME_COLLITIONHANDLER_H
