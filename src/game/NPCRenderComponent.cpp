#include "NPCRenderComponent.h"
#include "Game.h"
#include "StateComponent.h"

#include <iostream>

NPCRenderComponent::NPCRenderComponent(NPC *npcConfig) {
    this->npcConfig = *npcConfig;
}

void NPCRenderComponent::init() {

    destRect.w = (int)((float)(Game::getInstance().getConfig()->screenResolution.width)*WIDTH_SCALE);
    destRect.h = (int)((float)(Game::getInstance().getConfig()->screenResolution.height)*HEIGHT_SCALE);
    destRect.x = (int)entity->getComponent<PositionComponent>()->getX();
    destRect.y = (int)entity->getComponent<PositionComponent>()->getY();

    DELAY = 3;
    currentSprite = npcConfig.walk;
    _imageAmount  = WALK_IMAGE_AMOUNT;
    _imageCounter = 0;
    loadTexture();
}

void NPCRenderComponent::handleIncomingAction(){

    auto state = entity->getComponent<StateComponent>();

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
        default:
            LogManager::logError("Default Render Switch Action"); // TODO poner un log mejor
            break;
    }
}

int NPCRenderComponent::getJumpDuration(){
    return DELAY * JUMP_IMAGE_AMOUNT;
}


