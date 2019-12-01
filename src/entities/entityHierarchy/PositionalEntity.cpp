//
// Created by axel on 28/11/19.
//

#include "PositionalEntity.h"

int PositionalEntity::getX() {
    return position->getX();
}

int PositionalEntity::getY() {
    return position->getY();
}

int PositionalEntity::getZ() {
    return position->getZ();
}

void PositionalEntity::setPosition(int x, int y, int z){
    position->setPosition(x,y,z);
}
