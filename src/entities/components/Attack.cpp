//
// Created by axelmpm on 1/12/19.
//

#include "Attack.h"
#include "../entityHierarchy/Weapon.h"
#include "../entityHierarchy/AnimatedEntity.h"

Attack::Attack(State* state, AnimatedEntityCollitionHandler* animatedEntityCollitionHandler){

    this->state = state;
    this->collitionHandler = animatedEntityCollitionHandler;
}

void Attack::update() {
    handleCurrentState();
}

void Attack::handleCurrentState(){

    switch (state->current()) {
        case PUNCH:
            addressPunch();
            break;
        case KICK:
            addressKick();
            break;
        case JUMP_KICK:
            addressJumpKick();
            break;
        case PICK:
            addressPickIntent();
            break;
    }
}

void Attack::addressPunch(){

    list<Entity*>* punchables = collitionHandler->getAllKickableWithinKickingRange();

    for (auto punchable : *punchables){

        if (hasWeapon()){
            owner->notifySuccessfulAttack(weapon->useOn(punchable));
        }
        else{
            owner->notifySuccessfulAttack(punchable->setAttackedWith(PUNCH_ATTACK));
        }
        if (weaponBroke()){
            throwWeapon();
        }
    }

    punchables->clear();
    delete(punchables);
}

void Attack::addressKick() {

    list<Entity*>* kickables = collitionHandler->getAllKickableWithinKickingRange();

    for (auto kickable : *kickables){

        owner->notifySuccessfulAttack(kickable->setAttackedWith(KICK_ATTACK));
    }

    kickables->clear();
    delete(kickables);
}

void Attack::addressJumpKick(){

    list<Entity*>* kickables = collitionHandler->getAllKickableWithinKickingRange();

    for (auto kickable : *kickables){

        owner->notifySuccessfulAttack(kickable->setAttackedWith(JUMP_KICK_ATTACK));
    }

    kickables->clear();
    delete(kickables);
}

void Attack::addressPickIntent(){

    auto* pickable = collitionHandler->getClosestPickeableWithinPickingRange();
    setWeapon((Weapon*) pickable);
}

bool Attack::hasWeapon() {
    return weapon != nullptr;
}

bool Attack::weaponBroke() {
    if (weapon != nullptr){
        return weapon->broke();
    }
    else{
        return false;
    }
}

void Attack::throwWeapon() {
    weapon = nullptr;
}

void Attack::setWeapon(Weapon *weapon) {
    weapon->getPicked();
    this->weapon = weapon;
}
