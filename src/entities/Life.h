//
// Created by axel on 24/11/19.
//

#ifndef GAME_LIFE_H
#define GAME_LIFE_H


#include "components/State.h"
#include "components/appearances/LifeAppearance.h"

class Life {

public:
    Life(State* state);

private:
    LifeAppearance* appearance = nullptr;
    State* state = nullptr;

};


#endif //GAME_LIFE_H
