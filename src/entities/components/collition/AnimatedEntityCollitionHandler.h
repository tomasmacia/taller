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
    AnimatedEntityCollitionHandler(State* state, CollitionManager* collitionManager, CollitionBox* punchBox, CollitionBox* kickBox, CollitionBox* collitionBox,
                                    CollitionBox* pickBox);

    AnimatedEntityCollitionHandler(CollitionManager *collitionManager, CollitionBox *punchBox, CollitionBox *kickBox,
                                   CollitionBox *collitionBox, CollitionBox *pickBox);

    void setState(State *state);

    void update() override ;

    void reflectAllAttackCollitionBox();
    list<PhysicalEntity*>* getAllPunchableWithinPunchingRange();
    list<PhysicalEntity*>* getAllKickableWithinKickingRange();
    PhysicalEntity* getClosestPickeableWithinPickingRange();
    void moveAllCollitionBoxesKeepingRelativeDistancesTo(Point* destination);
    void correctDestination(Point* destination);
    void moveTowardsDestinationAndCorrect(Point* destination);
    void setDisconected();
    void setConnected();
    bool playerFliped();
    bool attackChanged();
    void adaptPunchingBox();

private:
    State* _state = nullptr;

    bool lastFacingState = false;
    AttackCode lastAttack = NO_WEAPON;
    int normalPunchingWidth;

    float KNIFE_WIDTH_SCALE_FACTOR = 1;
    float TUBE_WIDTH_SCALE_FACTOR = 1;

    CollitionBox* _blockingCollitionBox = nullptr;
    CollitionBox* _punchBox = nullptr;
    CollitionBox* _kickBox = nullptr;
    CollitionBox* _pickBox = nullptr;
};


#endif //GAME_ANIMATEDENTITYCOLLITIONHANDLER_H
