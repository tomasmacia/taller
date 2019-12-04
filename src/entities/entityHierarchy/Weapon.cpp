//
// Created by axel on 28/11/19.
//

#include "Weapon.h"

int Weapon::useOn(Entity *entity) {
    life->decreseBy(1);
}

void Weapon::getPicked() {
    collitionHandler->eraseCollitionBoxes();
    appearance->setTransparent();
}

Weapon::Weapon(CollitionHandler *collitionHandler, Life *life, Damage *damage, Score *score, Position *position,
               State *state, ScreenPosition *screenPosition, StateDrivenAppearance *appearance, Sound *sound)
        : UnanimatedEntity(collitionHandler, life, damage, score, position, state, screenPosition, appearance, sound) {
}
