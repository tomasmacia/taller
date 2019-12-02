//
// Created by axel on 25/11/19.
//

#ifndef GAME_ANIMATEDENTITYCOLLITIONHANDLER_H
#define GAME_ANIMATEDENTITYCOLLITIONHANDLER_H

#include "CollitionBox.h"
#include "CollitionHandler.h"
#include "../../../game/CollitionManager.h"

class AnimatedEntityCollitionHandler : public CollitionHandler{

public:
    AnimatedEntityCollitionHandler(CollitionManager* collitionManager, CollitionBox* punchBox, CollitionBox* kickBox, CollitionBox* collitionBox,
                                    CollitionBox* pickBox, State* state);

    list<Entity*>* getAllPunchableWithinPunchingRange();
    list<Entity*>* getAllKickableWithinKickingRange();
    Entity* getClosestPickeableWithinPickingRange();

private:
    CollitionBox* _punchBox = nullptr;
    CollitionBox* _kickBox = nullptr;
    CollitionBox* _pickBox = nullptr;
};


#endif //GAME_ANIMATEDENTITYCOLLITIONHANDLER_H
