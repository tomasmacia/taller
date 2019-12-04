//
// Created by axel on 24/11/19.
//

#ifndef GAME_KNIFE_H
#define GAME_KNIFE_H


#include "entityHierarchy/Weapon.h"
#include "components/appearances/KnifeAppearance.h"

class Knife : public Weapon{

public:
    Knife(CollitionHandler *collitionHandler, Life *life, Damage *damage, Score *score, Position *position,
          State *state, ScreenPosition *screenPosition, StateDrivenAppearance *appearance, Sound *sound);

    int useOn(Entity* entity) override ;
};


#endif //GAME_KNIFE_H
