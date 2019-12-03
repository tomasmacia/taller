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
