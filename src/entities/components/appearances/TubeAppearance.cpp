//
// Created by axelmpm on 3/12/19.
//

#include "TubeAppearance.h"

TubeAppearance::TubeAppearance(int w, int h, ScreenPosition *screenPosition, State *state, WeaponConfig config)
        : WeaponAppearance(w, h, screenPosition, state, config) {
    initDestRect(w,h);
    init();
}

void TubeAppearance::init() {

    DELAY = 3;
    STAND_IMAGE_AMOUNT = 1;

    currentSprite = config.sprite;
    _imageAmount  = STAND_IMAGE_AMOUNT;
    _imageCounter = 0;
    getCurrentSpriteDimentions();
}
