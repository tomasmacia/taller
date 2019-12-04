//
// Created by axel on 27/11/19.
//

#include "Entity.h"

Entity::Entity(CollitionHandler *collitionHandler) {
    this->collitionHandler = collitionHandler;
    collitionHandler->setOwnerToAllCollitionBox(this);
}

Entity::~Entity() {
    delete(collitionHandler);
}
