#include "StateDrivenAppearance.h"
#include "../State.h"

void StateDrivenAppearance::update() {

    handleCurrentState();
    getCurrentSpriteDimentions();
    loadNextImage();
    updateDestRectPosition();
}

void StateDrivenAppearance::loadNextImage(){

    currentSpriteWidth = currentSpriteWidth/_imageAmount;
    currentSpriteHeight = currentSpriteHeight;
    currentXInSprite = srcRect.w * (int)(_imageCounter / DELAY);

    _imageCounter++;
    
    if (_imageCounter == (_imageAmount * DELAY)){
        _state->setFinished();
        _imageCounter = 0;
    }

    _imageCounter = _imageCounter % (_imageAmount * DELAY);
}

bool StateDrivenAppearance::isFliped() {
    return _state->isFliped();
}

Renderable *StateDrivenAppearance::generateRenderable() {
    return new Renderable(currentSprite,srcRect,destRect,isFliped());
}

void StateDrivenAppearance::updateDestRectPosition(){

    destRect.x = _position->getX() - _screen->currentX;
    destRect.y = _position->getY();
}


