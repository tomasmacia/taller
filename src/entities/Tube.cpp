//
// Created by axel on 24/11/19.
//

#include "Tube.h"

int Tube::useOn(Entity *entity) {
    Weapon::useOn(entity);
    return entity->setAttackedWith(TUBE);
}