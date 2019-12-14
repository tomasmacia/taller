//
// Created by axelmpm on 2/12/19.
//

#include <iostream>
#include "AnimatedAppearance.h"

AnimatedAppearance::AnimatedAppearance(ScreenPosition* screenPosition, State* state, EntityConfig entityConfig) : StateDrivenAppearance(screenPosition,state){

    this->entityConfig = entityConfig;
}

void AnimatedAppearance::handleCurrentState(){

    if (_state->current() != previous) {
        previous = _state->current();
        switch (_state->current()) {
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
            switch (_state->getWeapon()) {
                case NO_WEAPON:
                    currentSprite = entityConfig.punch;
                    _imageAmount = PUNCH_IMAGE_AMOUNT;
                    break;
                case KNIFE:
                    currentSprite = entityConfig.knifeHit;
                    _imageAmount = KNIFE_ATTACK_IMAGE_AMOUNT;
                    break;
                case TUBE:
                    currentSprite = entityConfig.pipeHit;
                    _imageAmount = TUBE_ATTACK_IMAGE_AMOUNT;
                    break;
            }
        }
        if (_state->currentIsNotBlockingAction()) {
            if (_state->hasMovement()) {
                switch (_state->getWeapon()) {
                    case NO_WEAPON:
                        currentSprite = entityConfig.walk;
                        _imageAmount = WALK_IMAGE_AMOUNT;
                        break;
                    case KNIFE:
                        currentSprite = entityConfig.knifeWalk;
                        _imageAmount = KNIFE_WALK_IMAGE_AMOUNT;
                        break;
                    case TUBE:
                        currentSprite = entityConfig.pipeWalk;
                        _imageAmount = TUBE_WALK_IMAGE_AMOUNT;
                        break;
                }
            }
            else {
                switch (_state->getWeapon()) {
                    case NO_WEAPON:
                        currentSprite = entityConfig.stand;
                        _imageAmount = STAND_IMAGE_AMOUNT;
                        break;
                    case KNIFE:
                        currentSprite = entityConfig.knifeStand;
                        _imageAmount = STAND_IMAGE_AMOUNT;
                        break;
                    case TUBE:
                        currentSprite = entityConfig.pipeStand;
                        _imageAmount = STAND_IMAGE_AMOUNT;
                        break;
                }
            }
        }
        getCurrentSpriteDimentions();
    }
}
