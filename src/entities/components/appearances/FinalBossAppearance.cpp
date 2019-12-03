//
// Created by axelmpm on 1/12/19.
//

#include "FinalBossAppearance.h"

FinalBossAppearance::FinalBossAppearance(int w, int h, ScreenPosition* screenPosition, State* state, NPC npcConfig) :
        AnimatedAppearance(screenPosition, state, std::move(npcConfig)) {

    initDestRect(w,h);
    init();
}

void FinalBossAppearance::init() {

    DELAY = 3;
    STAND_IMAGE_AMOUNT = 1;
    WALK_IMAGE_AMOUNT = 5;
    JUMP_IMAGE_AMOUNT = 13;
    PUNCH_IMAGE_AMOUNT = 3;
    KICK_IMAGE_AMOUNT = 6;
    JUMP_KICK_IMAGE_AMOUNT = 13;
    CROUCH_IMAGE_AMOUNT = 4;
    //PICK_IMAGE_AMOUNT = -1; todo
    //BEING_ATTACKED_IMAGE_AMOUNT = -1;
    //DYING_IMAGE_AMOUNT = -1;
    //DEAD_IMAGE_AMOUNT = -1;

    currentSprite = entityConfig.walk;
    _imageAmount  = WALK_IMAGE_AMOUNT;
    _imageCounter = 0;
    getCurrentSpriteDimentions();
}