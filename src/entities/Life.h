//
// Created by axel on 24/11/19.
//

#ifndef GAME_LIFE_H
#define GAME_LIFE_H


#include "components/State.h"
#include "components/appearances/LifeAppearance.h"

class Life {

public:
    Life(int amount, State* state);

    bool empty();

private:
    int startingAmount;
    int current;

    LifeAppearance* appearance = nullptr;
    State* state = nullptr;

};


#endif //GAME_LIFE_H
