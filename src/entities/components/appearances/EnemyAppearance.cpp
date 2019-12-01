#include "EnemyAppearance.h"
#include "../State.h"

EnemyAppearance::EnemyAppearance(int w, int h, ScreenPosition* screenPosition, NPC *npcConfig) {
    this->npcConfig = *npcConfig;
    _screenPosition = screenPosition;
    initDestRect(w,h);
    init();
}

void EnemyAppearance::init() {

    DELAY = 3;
    WIDTH_SCALE = 0.2;
    HEIGHT_SCALE = 0.5;

    currentSprite = npcConfig.walk;
    _imageAmount  = WALK_IMAGE_AMOUNT;
    _imageCounter = 0;
    getCurrentSpriteDimentions();
}

void EnemyAppearance::handleCurrentState(){

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