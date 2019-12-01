//
// Created by axel on 28/11/19.
//

#include "Weapon.h"

Weapon::Weapon(Life *life) {

    this->life = life;
    life->initializeWith(USES_AMOUNT);
}

bool Weapon::broke() {
    return life->empty();
}
