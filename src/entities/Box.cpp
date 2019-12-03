//
// Created by axel on 24/11/19.
//

#include "Box.h"

int Box::setAttackedWith(AttackCode attack) {

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
