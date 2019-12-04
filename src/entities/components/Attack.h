//
// Created by axelmpm on 1/12/19.
//

#ifndef GAME_ATTACK_H
#define GAME_ATTACK_H

#include "State.h"
#include "../../enumerates/AttackCode.h"
#include "collition/AnimatedEntityCollitionHandler.h"

class AnimatedEntity;
class Weapon;
class Attack {
public:
    Attack(State* state, AnimatedEntityCollitionHandler* animatedEntityCollitionHandler);

    void update();

    void addressPunch();
    void addressKick();
    void addressJumpKick();
    void addressPickIntent();
    void setWeapon(Weapon* weapon);

    void setOwner(AnimatedEntity* owner){
        this->owner = owner;
    }

private:
    bool hasWeapon();
    bool weaponBroke();
    void throwWeapon();
    void handleCurrentState();

    AnimatedEntity* owner = nullptr;
    State* state = nullptr;
    AnimatedEntityCollitionHandler* collitionHandler = nullptr;
    Weapon* weapon = nullptr;
};


#endif //GAME_ATTACK_H
