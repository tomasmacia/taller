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

    void initializeWith(int amount, int amountOfLifes = 1);
    void decreseBy(int amount);
    bool empty();

    LifeAppearance* getAppearance(){
        return appearance;
    }

    int getLifeAmount(){
        return current;
    }

    int getAmountOfLifes(){
        return amountOfLifes;
    }

private:
    int amountOfLifes = 1;
    int startingAmount;
    int current;

    LifeAppearance* appearance = nullptr;
    State* state = nullptr;
};


#endif //GAME_LIFE_H
