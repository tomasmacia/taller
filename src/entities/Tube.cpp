//
// Created by axel on 24/11/19.
//

#include "Tube.h"

int Tube::useOn(Entity *entity) {
    Weapon::useOn(entity);
    return entity->setAttackedWith(TUBE);
}

Tube::Tube(CollitionHandler *collitionHandler, Life *life, Damage *damage, Score *score, Position *position,
           State *state, ScreenPosition *screenPosition, StateDrivenAppearance *appearance, Sound *sound) : Weapon(
        collitionHandler, life, damage, score, position, state, screenPosition, appearance, sound) {

}