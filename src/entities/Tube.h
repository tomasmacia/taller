//
// Created by axel on 24/11/19.
//

#ifndef GAME_TUBE_H
#define GAME_TUBE_H


#include "entityHierarchy/Weapon.h"
#include "components/appearances/TubeAppearance.h"

class Tube : public Weapon{

public:
    Tube(CollitionHandler *collitionHandler, Life *life, Damage *damage, Score *score, Position *position,
         State *state, ScreenPosition *screenPosition, StateDrivenAppearance *appearance, Sound *sound,
         CollitionHandler *pHandler, Life *pLife, Damage *pDamage, Score *pScore, Position *pPosition,
         State *pState, ScreenPosition *pPosition1, TubeAppearance *pAppearance, Sound *pSound);

    int useOn(Entity* entity) override ;
};


#endif //GAME_TUBE_H
