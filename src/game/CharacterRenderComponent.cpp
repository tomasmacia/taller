#include "CharacterRenderComponent.h"
#include "Game.h"
#include "StateComponent.h"

CharacterRenderComponent::CharacterRenderComponent(CharacterXML *characterConfig) {
    this->characterConfig = *characterConfig;
}

void CharacterRenderComponent::init() {
    destRect.w = (int)(Game::getInstance().getConfig()->screenResolution.width * 0.2);
    destRect.h = (int)(Game::getInstance().getConfig()->screenResolution.height * 0.50);
    destRect.x = (int)(Game::getInstance().getConfig()->screenResolution.width * 0.3);
    destRect.y = (int)(Game::getInstance().getConfig()->screenResolution.height * 0.3);

    DELAY = 5;
    currentSprite = characterConfig.stand;
    _imageAmount  = STAND_IMAGE_AMOUNT;
    loadTexture();
    _imageCounter = 0;
}

void CharacterRenderComponent::handleIncomingAction(){

    auto state = entity->getComponent<StateComponent>();

    switch (state->current()) {
        case NONE:
            currentSprite = characterConfig.stand;
            _imageAmount  = STAND_IMAGE_AMOUNT;
            break;
        case UP:
            currentSprite = characterConfig.walk;
            _imageAmount  = WALK_IMAGE_AMOUNT;
            break;
        case DOWN:
            currentSprite = characterConfig.walk;
            _imageAmount  = WALK_IMAGE_AMOUNT;
            break;
        case LEFT:
            if (state->facingRight()) flip();
            currentSprite = characterConfig.walk;
            _imageAmount  = WALK_IMAGE_AMOUNT;
            break;
        case RIGHT:
            if (state->facingLeft()) flip();
            currentSprite = characterConfig.walk;
            _imageAmount  = WALK_IMAGE_AMOUNT;
            break;
        case JUMP:
            currentSprite = characterConfig.jump;
            _imageAmount  = JUMP_IMAGE_AMOUNT;
            break;
        case PUNCH:
            currentSprite = characterConfig.punch;
            _imageAmount  = PUNCH_IMAGE_AMOUNT;
            break;
        case KICK:
            currentSprite = characterConfig.kick;
            _imageAmount  = KICK_IMAGE_AMOUNT;
            break;
        case JUMP_KICK:
            currentSprite = characterConfig.jumpkick;
            _imageAmount  = JUMP_KICK_IMAGE_AMOUNT;
            break;
        case CROUCH:
            currentSprite = characterConfig.crouch;
            _imageAmount  = CROUCH_IMAGE_AMOUNT;
            break;
        default:
            LogManager::logError("Default Render Switch Action"); // TODO poner un log mejor
            break;
    }
}

int CharacterRenderComponent::getJumpDuration(){
    return DELAY * JUMP_IMAGE_AMOUNT;
}

