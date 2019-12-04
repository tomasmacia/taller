//
// Created by axel on 24/11/19.
//

#include "Barrel.h"

int Barrel::setAttackedWith(AttackCode attack) {

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

Barrel::Barrel(CollitionHandler *collitionHandler, Life *life, Damage *damage, Score *score, Position *position,
               State *state, ScreenPosition *screenPosition, StateDrivenAppearance *appearance, Sound *sound,
               CollitionHandler *pHandler, Life *pLife, Damage *pDamage, Score *pScore, Position *pPosition,
               State *pState, ScreenPosition *pPosition1, BarrelAppearance *pAppearance, Sound *pSound)
        : Utillity(collitionHandler, life, damage, score, position, state, screenPosition, appearance, sound) {

}
