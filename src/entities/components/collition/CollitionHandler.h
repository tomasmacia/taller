//
// Created by axel on 25/11/19.
//

#ifndef GAME_COLLITIONHANDLER_H
#define GAME_COLLITIONHANDLER_H


#include "../Position.h"
#include "CollitionBox.h"
#include "../../../game/CollitionManager.h"

using namespace std;

class CollitionHandler {

public:
    CollitionHandler(CollitionManager* collitionManager);
    virtual ~CollitionHandler();

    void addCollitionBox(CollitionBox* collitionBox);
    void dragToRight(int amount);
    void setOwnerToAllCollitionBox(Entity* owner);

    void eraseCollitionBoxes();

protected:
    CollitionManager* _collitionManager = nullptr;

    list<CollitionBox*>* _collitionBoxes = nullptr;
};


#endif //GAME_COLLITIONHANDLER_H
