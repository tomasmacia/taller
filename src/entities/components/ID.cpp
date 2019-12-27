//
// Created by axel on 29/10/19.
//

#include "ID.h"

ID::ID(int id) {
    this->id = id;
}

int ID::get() {
    return id;
}

void ID::setNew(int newID){
    id = newID;
}