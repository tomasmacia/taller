//
// Created by axel on 25/11/19.
//

#ifndef GAME_ANIMATEDENTITYCOLLITIONHANDLER_H
#define GAME_ANIMATEDENTITYCOLLITIONHANDLER_H

#include "CollitionHandler.h"
#include "../ScreenPosition.h"
#include "../../entityHierarchy/PhysicalEntity.h"

class AnimatedEntityCollitionHandler : public CollitionHandler{

public:
    AnimatedEntityCollitionHandler(CollitionManager* collitionManager, CollitionBox* punchBox, CollitionBox* kickBox, CollitionBox* collitionBox,
                                    CollitionBox* pickBox);

    list<PhysicalEntity*>* getAllPunchableWithinPunchingRange();
    list<PhysicalEntity*>* getAllKickableWithinKickingRange();
    PhysicalEntity* getClosestPickeableWithinPickingRange();
    void moveAllCollitionBoxesKeepingRelativeDistancesTo(Point* destination);
    void correctDestination(Point* destination);
    void moveTowardsDestinationAndCorrect(Point* destination);
    void setDisconected();

    void setConnected();

private:
    CollitionBox* _blockingCollitionBox = nullptr;
    CollitionBox* _punchBox = nullptr;
    CollitionBox* _kickBox = nullptr;
    CollitionBox* _pickBox = nullptr;
};


#endif //GAME_ANIMATEDENTITYCOLLITIONHANDLER_H
