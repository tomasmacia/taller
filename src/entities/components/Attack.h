//
// Created by axelmpm on 1/12/19.
//

#ifndef GAME_ATTACK_H
#define GAME_ATTACK_H

#include "State.h"
#include "../../enumerates/AttackCode.h"
#include "collition/AnimatedEntityCollitionHandler.h"
#include "../entityHierarchy/Weapon.h"

class AnimatedEntity;
class Attack {
public:
    Attack(State* state, AnimatedEntityCollitionHandler* animatedEntityCollitionHandler);
    ~Attack();

    void update();

    void addressPunch();
    void addressKick();
    void addressJumpKick();
    void addressPickIntent();
    bool hasWeapon();
    bool weaponBroke();
    void dropWeapon();

    void setWeapon(Weapon* weapon);
    void setOwner(AnimatedEntity* owner){
        this->owner = owner;
    }
private:
    void handleCurrentState();

    list<PhysicalEntity*>* targets = nullptr;

    AnimatedEntity* owner = nullptr;
    State* state = nullptr;
    AnimatedEntityCollitionHandler* collitionHandler = nullptr;
    Weapon* weapon = nullptr;

    bool alreadyHasTargets();
    void stopAttacks();
};


#endif //GAME_ATTACK_H
