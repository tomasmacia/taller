//
// Created by axel on 24/11/19.
//

#include "Knife.h"

int Knife::useOn(Entity *entity) {
    Weapon::useOn(entity);
    return entity->setAttackedWith(KNIFE);
}

Knife::Knife(CollitionHandler *collitionHandler, Life *life, Damage *damage, Score *score, Position *position,
             State *state, ScreenPosition *screenPosition, StateDrivenAppearance *appearance, Sound *sound, int w, int h, int d) : Weapon(
        collitionHandler, life, damage, score, position, state, screenPosition, appearance, sound,w,h,d) {

}