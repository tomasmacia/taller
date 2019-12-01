//
// Created by axelmpm on 30/11/19.
//

#ifndef GAME_ANIMATEDENTITY_H
#define GAME_ANIMATEDENTITY_H

#include "PositionalEntity.h"
#include "../components/Sound.h"
#include "../components/collition/AnimatedEntityCollitionHandler.h"
#include "../components/Will.h"
#include "../components/State.h"
#include "../components/Position.h"
#include "../components/Physics.h"
#include "../components/ScreenPosition.h"
#include "../components/appearances/StateDrivenAppearance.h"
#include "../components/Sound.h"
#include "../components/Damage.h"
#include "../components/Attack.h"
#include "../Life.h"

class AnimatedEntity : public PositionalEntity {

public:
    AnimatedEntity(Will *will, State *state, AnimatedEntityCollitionHandler *collitionHandler, Position *position,
                   Physics *physics, ScreenPosition *screenPosition, StateDrivenAppearance *appearance, Sound *sound,
                   Damage *damage, Life *life, Attack *attack);

    ~AnimatedEntity();

    void update() override;
    Sendable* generateSendable() override;

    virtual void notifySuccessfulAttack(int score) {}
    bool dead();
    void drag();


    //GETTERS
    //===============================
    Life* getLife(){
        return life;
    }

    Damage* getDamage(){
        return damage;
    }

    int getWalkingSpeed(){
        return _wakingSpeed;
    }

protected:

    AnimatedEntity(Will* will, State* state, AnimatedEntityCollitionHandler* collitionHandler,
              Position* position, Physics* physics, ScreenPosition* screenPosition,
              StateDrivenAppearance* appearance, Sound* sound, Damage* damage, Life* life, Attack* attack);

    int _wakingSpeed;

    Life* life = nullptr;
    Damage* damage = nullptr;
    Will* will = nullptr;
    State* state = nullptr;
    AnimatedEntityCollitionHandler* collitionHandler = nullptr;
    Position* position = nullptr;
    Physics* physics = nullptr;
    ScreenPosition* screenPosition = nullptr;
    StateDrivenAppearance* appearance = nullptr;
    Sound* sound = nullptr;
    Attack* attack = nullptr;
};


#endif //GAME_ANIMATEDENTITY_H
