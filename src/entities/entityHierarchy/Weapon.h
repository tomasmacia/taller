//
// Created by axel on 28/11/19.
//

#ifndef GAME_WEAPON_H
#define GAME_WEAPON_H


#include "UnanimatedEntity.h"

class Weapon : public UnanimatedEntity{

public:
    Weapon(CollitionHandler *collitionHandler, Life *life, Damage *damage, Score *score, Position *position,
           State *state, ScreenPosition *screenPosition, StateDrivenAppearance *appearance, Sound *sound, int w, int h, int d);

    virtual int useOn(Entity* entity);
    void getPicked();

protected:
    int USES_AMOUNT = 3;
};



#endif //GAME_WEAPON_H
