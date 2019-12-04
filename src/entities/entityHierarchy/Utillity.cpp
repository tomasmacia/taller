//
// Created by axel on 28/11/19.
//

#include "Utillity.h"

Utillity::Utillity(CollitionHandler *collitionHandler, Life *life, Damage *damage, Score *score, Position *position,
                   State *state, ScreenPosition *screenPosition, StateDrivenAppearance *appearance, Sound *sound)
        : UnanimatedEntity(collitionHandler, life, damage, score, position, state, screenPosition, appearance, sound) {

}
