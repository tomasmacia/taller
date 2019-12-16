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
            currentSprite = config.damagedSprite;
            _imageAmount  = BEING_ATTACKED_IMAGE_AMOUNT;
            break;
        case DYING:
            currentSprite = config.brokenSprite;
            _imageAmount  = DYING_IMAGE_AMOUNT;
            break;
    }
    getCurrentSpriteDimentions();
}