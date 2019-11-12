#include "CharacterRenderComponent.h"
#include "StateComponent.h"

CharacterRenderComponent::CharacterRenderComponent(Entity* camera, CharacterXML characterConfig) {
    this->characterConfig = characterConfig;
    realSpritePath = characterConfig.stand;
    disconnectedSpritePath = characterConfig.disconnected;
    setCamera(camera);
}

void CharacterRenderComponent::init() {
    
    setDimentions();

    DELAY = 5;
    WIDTH_SCALE = 0.3; //el width de los codys es un poco mas grande
    destRect.w = (int)((float)(_camera->getWindowWidth())*WIDTH_SCALE);
    currentSprite = characterConfig.stand;
    _imageAmount  = STAND_IMAGE_AMOUNT;
    _imageCounter = 0;
    getCurrentSpriteDimentions();
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
        case END_UP:
            currentSprite = characterConfig.stand;
            _imageAmount  = STAND_IMAGE_AMOUNT;
            break;
        case DOWN:
            currentSprite = characterConfig.walk;
            _imageAmount  = WALK_IMAGE_AMOUNT;
            break;
        case END_DOWN:
            currentSprite = characterConfig.stand;
            _imageAmount  = STAND_IMAGE_AMOUNT;
            break;
        case LEFT:
            if (state->facingRight()) flip();
            currentSprite = characterConfig.walk;
            _imageAmount  = WALK_IMAGE_AMOUNT;
            break;
        case END_LEFT:
            currentSprite = characterConfig.stand;
            _imageAmount  = STAND_IMAGE_AMOUNT;
            break;
        case RIGHT:
            if (state->facingLeft()) flip();
            currentSprite = characterConfig.walk;
            _imageAmount  = WALK_IMAGE_AMOUNT;
            break;
        case END_RIGHT:
            currentSprite = characterConfig.stand;
            _imageAmount  = STAND_IMAGE_AMOUNT;
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
    }
}

int CharacterRenderComponent::getJumpDuration(){
    return DELAY * JUMP_IMAGE_AMOUNT;
}

void CharacterRenderComponent::setDisconnected() {
    currentSprite = disconnectedSpritePath;
}

void CharacterRenderComponent::setConnected() {
    currentSprite = realSpritePath;
}

 

