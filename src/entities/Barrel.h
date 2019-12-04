//
// Created by axel on 24/11/19.
//

#ifndef GAME_BARREL_H
#define GAME_BARREL_H


#include "entityHierarchy/Utillity.h"
#include "components/appearances/BarrelAppearance.h"

class Barrel : public Utillity {

public:
    Barrel(CollitionHandler *collitionHandler, Life *life, Damage *damage, Score *score, Position *position,
           State *state, ScreenPosition *screenPosition, StateDrivenAppearance *appearance, Sound *sound,
           CollitionHandler *pHandler, Life *pLife, Damage *pDamage, Score *pScore, Position *pPosition,
           State *pState, ScreenPosition *pPosition1, BarrelAppearance *pAppearance, Sound *pSound);

    int setAttackedWith(AttackCode attack) override ;

};


#endif //GAME_BARREL_H
