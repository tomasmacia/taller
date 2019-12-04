//
// Created by axel on 24/11/19.
//

#include "Life.h"

Life::Life(State *state) {
    this->state = state;
}

bool Life::empty() {
    return current <= 0;
}

void Life::decreseBy(int amount) {
    current -= amount;

    if (current <= 0){
        if (amountOfLifes > 1){
            amountOfLifes --;
            current = startingAmount;
        }
        else{
            state->setDying();
        }
    }
    appearance->update();
}

void Life::initializeWith(int amount, int amountOfLifes) {

    this->amountOfLifes = amountOfLifes;
    startingAmount = amount;
    current = amount;
}
