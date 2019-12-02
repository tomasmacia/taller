//
// Created by axel on 27/11/19.
//

#include "Entity.h"

Entity::Entity(CollitionHandler *collitionHandler) {
    this->collitionHandler = collitionHandler;
}

Entity::~Entity() {
    delete(collitionHandler);
}
