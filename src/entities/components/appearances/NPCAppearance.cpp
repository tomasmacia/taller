#include "NPCAppearance.h"
#include "../State.h"

NPCAppearance::NPCAppearance(int w, int h, Position* position, Screen* screen, NPC *npcConfig) {
    this->npcConfig = *npcConfig;
    _screen = screen;
    _position = position;
    initDestRect(w,h);
    init();
}

void NPCAppearance::init() {

    DELAY = 3;
    WIDTH_SCALE = 0.2;
    HEIGHT_SCALE = 0.5;

    currentSprite = npcConfig.walk;
    _imageAmount  = WALK_IMAGE_AMOUNT;
    _imageCounter = 0;
    getCurrentSpriteDimentions();
}

void NPCAppearance::handleCurrentState(){

    switch (_state->current()) {
        case NONE:
            currentSprite = npcConfig.walk;
            _imageAmount  = WALK_IMAGE_AMOUNT;
            break;
        case UP:
            currentSprite = npcConfig.walk;
            _imageAmount  = WALK_IMAGE_AMOUNT;
            break;
        case DOWN:
            currentSprite = npcConfig.walk;
            _imageAmount  = WALK_IMAGE_AMOUNT;
            break;
        case LEFT:
            currentSprite = npcConfig.walk;
            _imageAmount  = WALK_IMAGE_AMOUNT;
            break;
        case RIGHT:
            currentSprite = npcConfig.walk;
            _imageAmount  = WALK_IMAGE_AMOUNT;
            break;
    }
}