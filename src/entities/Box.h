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
        State *state, ScreenPosition *screenPosition, StateDrivenAppearance *appearance, Sound *sound);

    int setAttackedWith(AttackCode attack) override ;
};


#endif //GAME_BOX_H
