//
// Created by axel on 28/11/19.
//

#ifndef GAME_PHYSICALENTITY_H
#define GAME_PHYSICALENTITY_H

#include "Entity.h"
#include "../components/Position.h"
#include "../components/Damage.h"
#include "../Score.h"
#include "../Life.h"
#include "../components/appearances/StateDrivenAppearance.h"

class PhysicalEntity : public Entity{

public:
    PhysicalEntity(State* state, ScreenPosition* screenPosition, StateDrivenAppearance* appearance, Position *position, Damage *damage, Life *life, Score* score);
    ~PhysicalEntity();

    int getX();
    int getY();
    int getZ();
    void setPosition(int x, int y, int z);

protected:
    int lifes;
    int lifeAmount;

    Life* life = nullptr;
    Damage* damage = nullptr;
    Score* score = nullptr;
    Position* position = nullptr;
    State* state = nullptr;
    ScreenPosition* screenPosition = nullptr;
    StateDrivenAppearance* appearance = nullptr;
};


#endif //GAME_PHYSICALENTITY_H
