//
// Created by axel on 25/11/19.
//

#ifndef GAME_COLLITIONHANDLER_H
#define GAME_COLLITIONHANDLER_H


#include "../Position.h"
#include "CollitionBox.h"
#include "../State.h"
#include "../../../game/CollitionManager.h"
#include "../Point.h"

using namespace std;

class CollitionHandler {

public:
    CollitionHandler(CollitionManager* collitionManager);
    virtual ~CollitionHandler();

    void dragToRight(int amount);
    bool anyCollitions();
    void moveCollitionBoxes(Position* position);
    CollitionBox* addBlockingCollitionBox(int x, int y, int z, int w, int h, int d);
    CollitionBox* addNonBlockingCollitionBox(int x, int y, int z, int w, int h, int d);
    void addBlockingCollitionBox(CollitionBox* collitionBox);
    void addNonBlockingCollitionBox(CollitionBox* collitionBox);
    void setOwnerToAllCollitionBox(Entity* owner);

    int getCorrected(){
        return _corrected;
    }

protected:
    Point* _corrected = nullptr;
    State* _state = nullptr;
    CollitionManager* _collitionManager = nullptr;

    list<CollitionBox*>* _blockingCollitionBoxes = nullptr;
    list<CollitionBox*>* _collitionBoxes = nullptr;
};


#endif //GAME_COLLITIONHANDLER_H
