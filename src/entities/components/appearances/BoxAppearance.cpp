//
// Created by axelmpm on 2/12/19.
//

#include "BoxAppearance.h"

BoxAppearance::BoxAppearance(int w, int h, ScreenPosition *screenPosition, State *state, UtilityConfig config) :
                            UtilityAppearance(screenPosition,state,config){
    initDestRect(w,h);
    init();
}

void BoxAppearance::init() {

    DELAY = 3;
    STAND_IMAGE_AMOUNT = 1;
    BEING_ATTACKED_IMAGE_AMOUNT = 6;
    DYING_IMAGE_AMOUNT = 6;

    currentSprite = config.standSprite;
    _imageAmount  = STAND_IMAGE_AMOUNT;
    _imageCounter = 0;
    getCurrentSpriteDimentions();

}
