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
        case CROUCH:
            addressPickIntent();
            break;
        default:
            stopAttacks();
            break;
    }
}

void Attack::addressPunch(){ //se hace esta implementacion medio elaborada "al pedo" porque el acto de pegar dura mas que el de recibir el golpe y entonces podria pasar
                            //que el mismo golpe le pegue dos o tres o mas veces hasta matarlo

    if (alreadyHasTargets()){
        //pass
    }
    else{
        targets = collitionHandler->getAllPunchableWithinPunchingRange();

        for (auto target : *targets){

            if (hasWeapon()){
                owner->notifySuccessfulAttack(weapon->useOn(target));
            }
            else{
                owner->notifySuccessfulAttack(target->setAttackedWith(PUNCH_ATTACK));
            }
            if (weaponBroke()){
                dropWeapon();
            }
        }

        if (!targets->empty()){
            state->setHitting();
        }
    }
}

void Attack::addressKick() {

    if (alreadyHasTargets()){
        //pass
    }
    else{
        targets = collitionHandler->getAllKickableWithinKickingRange();

        for (auto target : *targets){

            owner->notifySuccessfulAttack(target->setAttackedWith(KICK_ATTACK));
        }
        if (!targets->empty()){
            state->setHitting();
        }
    }
}

void Attack::addressJumpKick(){

    if (alreadyHasTargets()){
        //pass
    }
    else{
        targets = collitionHandler->getAllKickableWithinKickingRange();

        for (auto target : *targets){

            owner->notifySuccessfulAttack(target->setAttackedWith(JUMP_KICK_ATTACK));
        }
        if (!targets->empty()){
            state->setHitting();
        }
    }
}

void Attack::addressPickIntent(){
    if (!hasWeapon()){
        auto* pickable = collitionHandler->getClosestPickeableWithinPickingRange();
        if (pickable != nullptr){
            setWeapon((Weapon*) pickable);
        }
    }
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

void Attack::dropWeapon() {
    state->dropWeapon();

    if (hasWeapon()){
        weapon->discard();
        weapon = nullptr;
    }
}

void Attack::setWeapon(Weapon *weapon) {
    if (hasWeapon()){
        dropWeapon();
    }
    state->equipWeapon(weapon->getType());
    weapon->getPicked();
    this->weapon = weapon;
}

Attack::~Attack() {
    if (targets != nullptr){
        targets->clear();
        delete(targets);
    }
    if (weapon != nullptr){
        weapon->discard();
    }
}

bool Attack::alreadyHasTargets() {

    if (targets != nullptr){
        return !targets->empty();
    }
    else{
        return false;
    }
}

void Attack::stopAttacks() {

    if (targets != nullptr){
        for (auto* target : *targets){
            target->stopBeingAttacked();
        }
        targets->clear();
        delete (targets);
        targets = nullptr;
    }
}
