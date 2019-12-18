//
// Created by axel on 24/11/19.
//

#include <iostream>
#include "Life.h"
#include <iostream>

Life::Life(State *state) {
    this->state = state;
    this->appearance = new LifeAppearance(nullptr);
}

bool Life::empty() {
    return current <= 0;
}

void Life::decreseBy(int amount) {

    if (!inTestMode) {
        current -= amount;
        appearance->hit(amount);

        if (current <= 0){

            amountOfLifes --;
            if (amountOfLifes > 0){
                current = startingAmount;
            }
        }
        if (appearance != nullptr){
            if (amountOfLifes == 0){
                appearance->noLifes();
            }
            appearance->update();
        }
    }
}

void Life::initializeWith(int amount, int amountOfLifes) {

    this->amountOfLifes = amountOfLifes;
    startingAmount = amount;
    current = amount;
}

list<Sendable *> Life::generateSendable() {
    list<Sendable*> sendables;

   // auto renderable = appearance->generateRenderable(); //TODO
   // sendables.push_back(new Sendable(renderable, nullptr));

    return sendables;
}

void Life::setTestMode() {
    inTestMode = true;
}

void Life::removeTestMode() {
    inTestMode = false;
}
