//
// Created by axel on 24/11/19.
//

#ifndef GAME_BOX_H
#define GAME_BOX_H


#include "entityHierarchy/Utillity.h"
#include "components/appearances/BoxAppearance.h"

class Box  : public Utillity{

public:
    Box(CollitionHandler *collitionHandler, Life *life, Damage *damage, Score *score, Position *position,
        State *state, ScreenPosition *screenPosition, StateDrivenAppearance *appearance, Sound *sound,
        CollitionHandler *pHandler, Life *pLife, Damage *pDamage, Score *pScore, Position *pPosition,
        State *pState, ScreenPosition *pPosition1, BoxAppearance *pAppearance, Sound *pSound);

    int setAttackedWith(AttackCode attack) override ;
};


#endif //GAME_BOX_H
