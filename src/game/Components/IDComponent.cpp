//
// Created by axel on 29/10/19.
//

#include "IDComponent.h"

IDComponent::IDComponent(int id) {
    this->id = id;
}

int IDComponent::getId() {
    return id;
}

void IDComponent::setNewID(int newID){
    id = newID;
}