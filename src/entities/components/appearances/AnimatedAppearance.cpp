//
// Created by axelmpm on 2/12/19.
//

#include "AnimatedAppearance.h"

AnimatedAppearance::AnimatedAppearance(ScreenPosition* screenPosition, State* state, EntityConfig entityConfig) : StateDrivenAppearance(screenPosition,state){

    this->entityConfig = entityConfig;
}

void AnimatedAppearance::handleCurrentState(){

    switch (_state->current()) {
        case JUMP:
            currentSprite = entityConfig.jump;
            _imageAmount  = JUMP_IMAGE_AMOUNT;
            break;
        case PUNCH:
            currentSprite = entityConfig.punch;
            _imageAmount  = PUNCH_IMAGE_AMOUNT;
            break;
        case KICK:
            currentSprite = entityConfig.kick;
            _imageAmount  = KICK_IMAGE_AMOUNT;
            break;
        case JUMP_KICK:
            currentSprite = entityConfig.jumpkick;
            _imageAmount  = JUMP_KICK_IMAGE_AMOUNT;
            break;
        case CROUCH:
            currentSprite = entityConfig.crouch;
            _imageAmount  = CROUCH_IMAGE_AMOUNT;
            break;
        case PICK:
            //currentSprite = entityConfig.pick;
            //_imageAmount  = PICK_IMAGE_AMOUNT; todo
            break;
        case BEING_ATTACKED:
            //currentSprite = entityConfig.being_attacked;
            //_imageAmount  = BEING_ATTACKED_IMAGE_AMOUNT; todo
            break;
        case DYING:
            //currentSprite = entityConfig.dying;
            //_imageAmount  = DYING_IMAGE_AMOUNT; todo
            break;
    }

    if (_state->currentIsNotBlockingAction()){
        if (_state->hasMovement()){
            currentSprite = entityConfig.walk;
            _imageAmount  = WALK_IMAGE_AMOUNT;
        }
        else{
            currentSprite = entityConfig.stand;
            _imageAmount  = STAND_IMAGE_AMOUNT;
        }
    }
}
