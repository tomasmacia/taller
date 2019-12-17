//
// Created by axel on 24/11/19.
//

#ifndef GAME_LIFE_H
#define GAME_LIFE_H


#include "components/State.h"
#include "components/appearances/LifeAppearance.h"

class Life : public Entity{

public:
    Life(State* state);

    void update() override {}
    void initializeWith(int amount, int amountOfLifes = 1);
    list<Sendable*> generateSendable() override ;
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
    int current;int amountOfLifes = 1;

    void setYPositionToLifeBar(int a){
        appearance->setYPosition(a);
    }

private:
    
    int startingAmount;
    

    LifeAppearance* appearance = nullptr;
    State* state = nullptr;
};


#endif //GAME_LIFE_H
