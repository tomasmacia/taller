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
          State *state, ScreenPosition *screenPosition, StateDrivenAppearance *appearance, Sound *sound, int w, int h, int d);

    int useOn(Entity* entity) override ;
    int KNIFE_LIFE_AMOUNT = 3;
};


#endif //GAME_KNIFE_H
