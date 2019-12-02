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
#include "../components/Sound.h"
#include "../components/ScreenPosition.h"
#include "../components/appearances/StateDrivenAppearance.h"

class PhysicalEntity : public Entity{

public:
    PhysicalEntity(CollitionHandler* collitionHandler, Life *life, Damage *damage, Score* score, Position *position,
                   State* state, ScreenPosition* screenPosition, StateDrivenAppearance* appearance, Sound* sound);
    virtual ~PhysicalEntity();

    virtual void update() override ;
    Sendable* generateSendable() override ;

    bool lifeEmpty();
    bool dead();
    int getX();
    int getY();
    int getZ();
    void setPosition(int x, int y, int z);

protected:

    Life* life = nullptr;
    Damage* damage = nullptr;
    Score* score = nullptr;
    Position* position = nullptr;
    State* state = nullptr;
    ScreenPosition* screenPosition = nullptr;
    StateDrivenAppearance* appearance = nullptr;
    Sound* sound = nullptr;
};


#endif //GAME_PHYSICALENTITY_H
