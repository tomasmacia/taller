//
// Created by axelmpm on 30/11/19.
//

#ifndef GAME_ANIMATEDENTITY_H
#define GAME_ANIMATEDENTITY_H

#include <iostream>
#include "PhysicalEntity.h"
#include "../components/Will.h"
#include "../components/Physics.h"
#include "../components/Attack.h"

class AnimatedEntity : public PhysicalEntity {

public:
    AnimatedEntity(CollitionHandler* collitionHandler, Life *life, Damage *damage, Score* score, Position *position,
                   State* state, ScreenPosition* screenPosition, StateDrivenAppearance* appearance, Sound* sound,
                   Will* will, Physics* physics, Attack* attack);

    ~AnimatedEntity();

    void update() override;

    virtual void notifySuccessfulAttack(int score) { cout<<"pegue"<<endl;}
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
    int _wakingSpeed;

    Will* will = nullptr;
    Physics* physics = nullptr;
    Attack* attack = nullptr;
};


#endif //GAME_ANIMATEDENTITY_H
