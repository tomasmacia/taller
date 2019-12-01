//
// Created by axel on 24/11/19.
//

#include "Tube.h"

int Tube::useOn(Entity *entity) {

    life->decreseBy(1);
    return entity->setAttackedWith(KNIFE);
}