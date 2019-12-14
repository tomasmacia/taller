//
// Created by axelmpm on 2/12/19.
//

#include "UnanimatedEntity.h"

UnanimatedEntity::UnanimatedEntity(CollitionHandler *collitionHandler, Life *life, Damage *damage, Score *score,
                                   Position *position, State *state, ScreenPosition *screenPosition,
                                   StateDrivenAppearance *appearance, Sound *sound, int w, int h, int d) :

                                    PhysicalEntity(collitionHandler, life, damage, score, position, state,
                                                    screenPosition, appearance, sound,w,h,d){
}

bool UnanimatedEntity::broke() {
    return lifeEmpty();
}

void UnanimatedEntity::update() {
    state->update();
    sound->update();
    appearance->update();
}
