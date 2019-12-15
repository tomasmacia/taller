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
         State *state, ScreenPosition *screenPosition, StateDrivenAppearance *appearance, Sound *sound, int w, int h, int d);

    int useOn(Entity* entity) override ;

    int TUBE_LIFE_AMOUNT = 3;
};


#endif //GAME_TUBE_H
