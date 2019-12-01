//
// Created by axelmpm on 1/12/19.
//

#ifndef GAME_ATTACKCODE_H
#define GAME_ATTACK_H


#include "../entityHierarchy/Weapon.h"
#include "State.h"
#include "../../enumerates/AttackCode.h"
#include "collition/AnimatedEntityCollitionHandler.h"

class Attack {
public:
    Attack(AnimatedEntity* owner, State* state, AnimatedEntityCollitionHandler* animatedEntityCollitionHandler);

    void update();

    void addressPunch();
    void addressKick();
    void addressJumpKick();
    void addressPickIntent();

    void setWeapon(Weapon* weapon){
        this->weapon = weapon;
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


#endif //GAME_ATTACKCODE_H
