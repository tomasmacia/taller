//
// Created by axel on 24/11/19.
//

#include "Box.h"

int Box::setAttackedWith(AttackCode attack) {

    if (state->current() != BEING_ATTACKED){

        PhysicalEntity::setAttackedWith(attack);
        int damageInflicted = damage->boxAttackedWith(attack);

        life->decreseBy(damageInflicted);

        if (broke()){
            return score->boxBroken();
        }
        else{
            return score->boxAttackedWith(attack);
        }
    }

    return 0; // TODO: tiene sentido?
}

Box::Box(CollitionHandler *collitionHandler, Life *life, Damage *damage, Score *score, Position *position, State *state,
         ScreenPosition *screenPosition, StateDrivenAppearance *appearance, Sound *sound, int w, int h, int d) : Utillity(collitionHandler,
                                                                                                     life, damage,
                                                                                                     score, position,
                                                                                                     state,
                                                                                                     screenPosition,
                                                                                                     appearance,
                                                                                                     sound,w,h,d) {
    this->life->initializeWith(BOX_LIFE_AMOUNT);
}