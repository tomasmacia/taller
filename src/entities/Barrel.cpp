//
// Created by axel on 24/11/19.
//

#include "Barrel.h"

int Barrel::setAttackedWith(AttackCode attack) {

    if (state->current() != BEING_ATTACKED){
        PhysicalEntity::setAttackedWith(attack);
        int damageInflicted = damage->barrelAttackedWith(attack);

        life->decreseBy(damageInflicted);

        if (broke()){
            return score->barrelBroken();
        }
        else{
            return score->barrelAttackedWith(attack);
        }
    }
}

Barrel::Barrel(CollitionHandler *collitionHandler, Life *life, Damage *damage, Score *score, Position *position,
               State *state, ScreenPosition *screenPosition, StateDrivenAppearance *appearance, Sound *sound, int w, int h, int d)
        : Utillity(collitionHandler, life, damage, score, position, state, screenPosition, appearance, sound,w,h,d) {

    this->life->initializeWith(BARREL_LIFE_AMOUNT);
}