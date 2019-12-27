#include "EnemyAppearance.h"

#include <utility>
#include <iostream>

EnemyAppearance::EnemyAppearance(int w, int h, ScreenPosition* screenPosition, State* state, NPC npcConfig) : AnimatedAppearance(
        screenPosition, state, std::move(npcConfig)) {
    initDestRect(w,h);
    init();
}

void EnemyAppearance::init() {

    DELAY = 3;
    STAND_IMAGE_AMOUNT = 1;
    WALK_IMAGE_AMOUNT = 5;
    JUMP_IMAGE_AMOUNT = 13;
    PUNCH_IMAGE_AMOUNT = 3;
    KICK_IMAGE_AMOUNT = 6;
    JUMP_KICK_IMAGE_AMOUNT = 13;
    CROUCH_IMAGE_AMOUNT = 4;
    BEING_ATTACKED_IMAGE_AMOUNT = 5;
    DYING_IMAGE_AMOUNT = 7;

    currentSprite = entityConfig.stand;
    _imageAmount  = STAND_IMAGE_AMOUNT;
    _imageCounter = 0;
    getCurrentSpriteDimentions();
}