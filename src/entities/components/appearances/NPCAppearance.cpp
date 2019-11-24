#include "NPCAppearance.h"
#include "../State.h"

NPCAppearance::NPCAppearance(Entity* camera, NPC *npcConfig) {
    this->npcConfig = *npcConfig;
    setCamera(camera);
}

void NPCAppearance::init() {

    setDimentions();

    DELAY = 3;
    currentSprite = npcConfig.walk;
    _imageAmount  = WALK_IMAGE_AMOUNT;
    _imageCounter = 0;
    getCurrentSpriteDimentions();
}

void NPCAppearance::handleIncomingAction(){

    auto state = entity->getComponent<State>();

    switch (state->current()) {
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
            if (state->facingRight()) flip();
            currentSprite = npcConfig.walk;
            _imageAmount  = WALK_IMAGE_AMOUNT;
            break;
        case RIGHT:
            if (state->facingLeft()) flip();
            currentSprite = npcConfig.walk;
            _imageAmount  = WALK_IMAGE_AMOUNT;
            break;
    }
}

int NPCAppearance::getJumpDuration(){
    return DELAY * JUMP_IMAGE_AMOUNT;
}


