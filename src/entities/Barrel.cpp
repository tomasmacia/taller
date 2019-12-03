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
