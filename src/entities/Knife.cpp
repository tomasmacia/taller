//
// Created by axel on 24/11/19.
//

#include "Knife.h"

int Knife::useOn(Entity *entity) {
    Weapon::useOn(entity);
    return entity->setAttackedWith(KNIFE);
}

Knife::Knife(CollitionHandler *collitionHandler, Life *life, Damage *damage, Score *score, Position *position,
             State *state, ScreenPosition *screenPosition, StateDrivenAppearance *appearance, Sound *sound,
             CollitionHandler *pHandler, Life *pLife, Damage *pDamage, Score *pScore, Position *pPosition,
             State *pState, ScreenPosition *pPosition1, KnifeAppearance *pAppearance, Sound *pSound)
        : Weapon(collitionHandler, life, damage, score, position, state, screenPosition, appearance, sound) {

}
