//
// Created by axel on 25/11/19.
//

#ifndef GAME_COLLITIONHANDLER_H
#define GAME_COLLITIONHANDLER_H


#include "../Position.h"
#include "CollitionBox.h"
#include "../State.h"
#include "../../../game/CollitionManager.h"
using namespace std;

class CollitionHandler {

public:
    bool noCollitionsIn(int newX, int newY, int newZ);
    void moveCollitionBoxes(Position* position);

protected:
    State* _state = nullptr;

    CollitionBox* _collitionBox = nullptr;
    CollitionManager* _collitionManager = nullptr;

    list<CollitionBox*>* _collitionBoxes = nullptr;

};


#endif //GAME_COLLITIONHANDLER_H
