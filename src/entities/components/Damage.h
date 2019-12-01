//
// Created by axel on 24/11/19.
//

#ifndef GAME_DAMAGE_H
#define GAME_DAMAGE_H


#include "State.h"
#include "appearances/DamageAppearance.h"

class Damage {

public:
    Damage(State* state);

private:
    DamageAppearance* appearance = nullptr;
    State* state = nullptr;
};


#endif //GAME_DAMAGE_H
