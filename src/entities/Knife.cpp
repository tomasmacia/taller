//
// Created by axel on 24/11/19.
//

#include "Knife.h"

int Knife::useOn(Entity *entity) {

    life->decreseBy(1);
    return entity->setAttackedWith(KNIFE);
}
