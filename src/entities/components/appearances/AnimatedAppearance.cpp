//
// Created by axelmpm on 2/12/19.
//

#include <iostream>
#include "AnimatedAppearance.h"

AnimatedAppearance::AnimatedAppearance(ScreenPosition* screenPosition, State* state, EntityConfig entityConfig) : StateDrivenAppearance(screenPosition,state){

    this->entityConfig = entityConfig;
}

void AnimatedAppearance::handleCurrentState(){

    if (_state->current() != previous || weaponWasBeingDroped) {
        if (weaponWasBeingDroped){
            weaponWasBeingDroped = false;
        }
        previous = _state->current();
        switch (_state->current()) {
            case END_JUMP:
                currentSprite = entityConfig.stand;
                _imageAmount = END_JUMP_IMAGE_AMOUNT;
                break;
            case JUMP:
                currentSprite = entityConfig.jump;
                _imageAmount = JUMP_IMAGE_AMOUNT;
                break;
            case KICK:
                currentSprite = entityConfig.kick;
                _imageAmount = KICK_IMAGE_AMOUNT;
                break;
            case JUMP_KICK:
                currentSprite = entityConfig.jumpkick;
                _imageAmount = JUMP_KICK_IMAGE_AMOUNT;
                break;
            case CROUCH:
                currentSprite = entityConfig.crouch;
                _imageAmount = CROUCH_IMAGE_AMOUNT;
                break;
            case BEING_ATTACKED:
                currentSprite = entityConfig.beingAttacked;
                _imageAmount = BEING_ATTACKED_IMAGE_AMOUNT;
                break;
            case DYING:
                currentSprite = entityConfig.dying;
                _imageAmount  = DYING_IMAGE_AMOUNT;
                break;
        }
        if (_state->current() == PUNCH) {
            auto currentWeapon = _state->getWeapon();
            auto prevWeapon = _state->getPrevWeapon();
            bool isDroping = _state->dropingWeapon();

            if (currentWeapon == NO_WEAPON && !isDroping){
                currentSprite = entityConfig.punch;
                _imageAmount = PUNCH_IMAGE_AMOUNT;
            }
            else if(currentWeapon == KNIFE || (isDroping && prevWeapon == KNIFE)){
                currentSprite = entityConfig.knifeHit;
                _imageAmount = KNIFE_ATTACK_IMAGE_AMOUNT;
            }
            else if(currentWeapon == TUBE || (isDroping && prevWeapon == TUBE)){
                currentSprite = entityConfig.pipeHit;
                _imageAmount = TUBE_ATTACK_IMAGE_AMOUNT;
            }
        }
        if (_state->currentIsNotBlockingAction()) {
            if (_state->hasMovement()) {
                auto currentWeapon = _state->getWeapon();
                auto prevWeapon = _state->getPrevWeapon();
                bool isDroping = _state->dropingWeapon();

                if (currentWeapon == NO_WEAPON && !isDroping){
                    currentSprite = entityConfig.walk;
                    _imageAmount = WALK_IMAGE_AMOUNT;
                }
                else if(currentWeapon == KNIFE || (isDroping && prevWeapon == KNIFE)){
                    currentSprite = entityConfig.knifeWalk;
                    _imageAmount = KNIFE_WALK_IMAGE_AMOUNT;
                }
                else if(currentWeapon == TUBE || (isDroping && prevWeapon == TUBE)){
                    currentSprite = entityConfig.pipeWalk;
                    _imageAmount = TUBE_WALK_IMAGE_AMOUNT;
                }
                if (isDroping){
                    weaponWasBeingDroped = true;
                    _state->endDropingWeapon();
                }
            }
            else {
                auto currentWeapon = _state->getWeapon();
                auto prevWeapon = _state->getPrevWeapon();
                bool isDroping = _state->dropingWeapon();

                if (currentWeapon == NO_WEAPON && !isDroping){
                    currentSprite = entityConfig.stand;
                    _imageAmount = STAND_IMAGE_AMOUNT;
                }
                else if(currentWeapon == KNIFE || (isDroping && prevWeapon == KNIFE)){
                    currentSprite = entityConfig.knifeStand;
                    _imageAmount = STAND_IMAGE_AMOUNT;
                }
                else if(currentWeapon == TUBE || (isDroping && prevWeapon == TUBE)){
                    currentSprite = entityConfig.pipeStand;
                    _imageAmount = STAND_IMAGE_AMOUNT;
                }
                if (isDroping){
                    weaponWasBeingDroped = true;
                    _state->endDropingWeapon();
                }
            }
        }
        getCurrentSpriteDimentions();
    }
}
