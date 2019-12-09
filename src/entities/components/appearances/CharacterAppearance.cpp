#include "CharacterAppearance.h"
#include "../State.h"

CharacterAppearance::CharacterAppearance(int w, int h, Position *position, ScreenPosition *screenPosition, State *state,
                                         CharacterXML characterConfig) : AnimatedAppearance(screenPosition, state, characterConfig) {

    disconnectedSpritePath = characterConfig.disconnected;
    realSpritePath = entityConfig.stand;
    initDestRect(w,h);
    init();
}

void CharacterAppearance::init() {

    DELAY = 5;
    STAND_IMAGE_AMOUNT = 1;
    WALK_IMAGE_AMOUNT = 9;
    JUMP_IMAGE_AMOUNT = 13;
    PUNCH_IMAGE_AMOUNT = 3;
    CROUCH_IMAGE_AMOUNT = 4;
    KICK_IMAGE_AMOUNT = 6;
    JUMP_KICK_IMAGE_AMOUNT = 13;
    BEING_ATTACKED_IMAGE_AMOUNT = 4;
    DYING_IMAGE_AMOUNT = 8;

    currentSprite = entityConfig.stand;
    _imageAmount  = STAND_IMAGE_AMOUNT;
    _imageCounter = 0;
    getCurrentSpriteDimentions();
}

void CharacterAppearance::setDisconnected() {
    currentSprite = disconnectedSpritePath;
}

void CharacterAppearance::setConnected() {
    currentSprite = realSpritePath;
}