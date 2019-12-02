//
// Created by axelmpm on 2/12/19.
//

#include "UnanimatedEntity.h"

UnanimatedEntity::UnanimatedEntity(CollitionHandler *collitionHandler, Life *life, Damage *damage, Score *score,
                                   Position *position, State *state, ScreenPosition *screenPosition,
                                   StateDrivenAppearance *appearance, Sound *sound) :

                                    PhysicalEntity(collitionHandler, life, damage, score, position, state,
                                                    screenPosition, appearance, sound){
}

bool UnanimatedEntity::broke() {
    return lifeEmpty();
}
