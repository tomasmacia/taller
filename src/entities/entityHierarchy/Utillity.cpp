//
// Created by axel on 28/11/19.
//

#include "Utillity.h"

Utillity::Utillity(Life *life) {

    this->life = life;
}

bool Utillity::broke() {
    return life->empty();
}


