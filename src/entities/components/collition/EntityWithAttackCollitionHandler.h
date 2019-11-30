//
// Created by axel on 25/11/19.
//

#ifndef GAME_ENTITYWITHATTACKCOLLITIONHANDLER_H
#define GAME_ENTITYWITHATTACKCOLLITIONHANDLER_H


#include "../../../game/CollitionManager.h"
#include "CollitionHandler.h"
#include "collitionBoxHierarchy/CollitionBox.h"

class EntityWithAttackCollitionHandler : public CollitionHandler{

public:
    EntityWithAttackCollitionHandler(CollitionBox* punchBox, CollitionBox* kickBox, CollitionBox* collitionBox, CollitionManager* collitionManager, State* state);
    ~EntityWithAttackCollitionHandler();

    void update();
    void handleCurrentState();

private:
    void addressAttack(CollitionBox* attackingBoxInUse);

    CollitionBox* _punchBox = nullptr;
    CollitionBox* _kickBox = nullptr;
};


#endif //GAME_ENTITYWITHATTACKCOLLITIONHANDLER_H
