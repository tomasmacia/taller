//
// Created by axelmpm on 2/12/19.
//

#include <iostream>
#include "UtilityAppearance.h"

UtilityAppearance::UtilityAppearance(ScreenPosition *screenPosition, State *state, UtilityConfig config) :
                    StateDrivenAppearance(screenPosition,state){

    this->config = config;
}

void UtilityAppearance::handleCurrentState(){

    switch (_state->current()) {
        case NONE:
            currentSprite = config.standSprite;
            _imageAmount  = STAND_IMAGE_AMOUNT;
            break;
        case BEING_ATTACKED:
            currentSprite = config.beingAttacked;
            std::cout<<"attacked: "<<currentSprite<<std::endl;
            _imageAmount  = BEING_ATTACKED_IMAGE_AMOUNT;
            break;
        case DYING:
            currentSprite = config.dying;
            std::cout<<"dying: "<<currentSprite<<std::endl;
            _imageAmount  = DYING_IMAGE_AMOUNT;
            break;
    }
}