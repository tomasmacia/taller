//
// Created by axel on 25/11/19.
//

#ifndef GAME_ANIMATEDENTITYCOLLITIONHANDLER_H
#define GAME_ANIMATEDENTITYCOLLITIONHANDLER_H


#include "../../../game/CollitionManager.h"
#include "CollitionHandler.h"
#include "CollitionBox.h"

class AnimatedEntityCollitionHandler : public CollitionHandler{

public:
    AnimatedEntityCollitionHandler(CollitionBox* punchBox, CollitionBox* kickBox, CollitionBox* collitionBox, CollitionManager* collitionManager, State* state);
    ~AnimatedEntityCollitionHandler();

    void update();
    void handleCurrentState();

    list<Entity*>* getAllPunchableWithinPunchingRange();
    list<Entity*>* getAllKickableWithinKickingRange();
    Entity* getClosestPickeableWithinPickingRange();

private:
    void addressAttack(CollitionBox* attackingBoxInUse);
    void addressPickIntent();

    CollitionBox* _punchBox = nullptr;
    CollitionBox* _kickBox = nullptr;
    CollitionBox* _pickBox = nullptr;
};


#endif //GAME_ANIMATEDENTITYCOLLITIONHANDLER_H
