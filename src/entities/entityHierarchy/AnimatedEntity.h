//
// Created by axelmpm on 30/11/19.
//

#ifndef GAME_ANIMATEDENTITY_H
#define GAME_ANIMATEDENTITY_H

#include "PhysicalEntity.h"
#include "../components/collition/AnimatedEntityCollitionHandler.h"
#include "../components/Will.h"
#include "../components/Physics.h"
#include "../components/Sound.h"
#include "../components/Attack.h"

class AnimatedEntity : public PhysicalEntity {

public:
    AnimatedEntity(Will *will, State *state, AnimatedEntityCollitionHandler *collitionHandler, Position *position,
                   Physics *physics, ScreenPosition *screenPosition, StateDrivenAppearance *appearance, Sound *sound,
                   Damage *damage, Life *life, Attack *attack);

    ~AnimatedEntity();

    void update() override;
    Sendable* generateSendable() override;

    virtual void notifySuccessfulAttack(int score) {}
    bool lifeEmpty();
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
              StateDrivenAppearance* appearance, Sound* sound, Damage* damage, Life* life, Score* score, Attack* attack);

    int _wakingSpeed;

    AnimatedEntityCollitionHandler* collitionHandler = nullptr;
    Physics* physics = nullptr;
    Sound* sound = nullptr;
    Attack* attack = nullptr;
    Will* will = nullptr;
};


#endif //GAME_ANIMATEDENTITY_H
