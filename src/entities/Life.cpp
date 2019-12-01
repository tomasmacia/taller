//
// Created by axel on 24/11/19.
//

#include "Life.h"

Life::Life(int amount, State *state) {

    this->startingAmount = amount;
    this->current = amount;

    this->state = state;
}

bool Life::empty() {
    return current <= 0;
}
