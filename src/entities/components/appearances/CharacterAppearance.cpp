#include "CharacterAppearance.h"
#include "../State.h"

CharacterAppearance::CharacterAppearance(int w, int h, Position *position, ScreenPosition *screenPosition, State *state,
                                         const CharacterXML &characterConfig) : StateDrivenAppearance(screenPosition, state) {

    this->characterConfig = characterConfig;
    realSpritePath = characterConfig.stand;
    disconnectedSpritePath = characterConfig.disconnected;
    initDestRect(w,h);
    init();
}

void CharacterAppearance::init() {

    DELAY = 5;

    currentSprite = characterConfig.stand;
    _imageAmount  = STAND_IMAGE_AMOUNT;
    _imageCounter = 0;
    getCurrentSpriteDimentions();
}

void CharacterAppearance::handleCurrentState(){

    switch (_state->current()) {
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

    if (_state->currentIsNotBlockingAction()){
        if (_state->hasMovement()){
            currentSprite = characterConfig.walk;
            _imageAmount  = WALK_IMAGE_AMOUNT;
        }
        else{
            currentSprite = characterConfig.stand;
            _imageAmount  = STAND_IMAGE_AMOUNT;
        }
    }
}

void CharacterAppearance::setDisconnected() {
    currentSprite = disconnectedSpritePath;
}

void CharacterAppearance::setConnected() {
    currentSprite = realSpritePath;
}
 

