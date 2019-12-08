//
// Created by axel on 28/11/19.
//

#ifndef GAME_UTILLITY_H
#define GAME_UTILLITY_H

#include "UnanimatedEntity.h"

class Utillity : public UnanimatedEntity{

protected:
    Utillity(CollitionHandler *collitionHandler, Life *life, Damage *damage, Score *score, Position *position,
             State *state, ScreenPosition *screenPosition, StateDrivenAppearance *appearance, Sound *sound, int w, int h, int d);
};


#endif //GAME_UTILLITY_H
