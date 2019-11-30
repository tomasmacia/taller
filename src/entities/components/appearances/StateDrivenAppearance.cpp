#include "StateDrivenAppearance.h"
#include "../State.h"

void StateDrivenAppearance::update() {

    handleCurrentState();
    loadNextImage();
    updateDestRectPosition();
}

void StateDrivenAppearance::loadNextImage(){

    currentSpriteWidth = currentSpriteWidth/_imageAmount;
    currentSpriteHeight = currentSpriteHeight;
    srcRect.x = srcRect.w * (int)(_imageCounter / DELAY);

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

Renderable *StateDrivenAppearance::actuallyGenerateRenderable() {
    return new Renderable(currentSprite,srcRect,destRect,isFliped());
}

void StateDrivenAppearance::updateDestRectPosition(){
    
    _screenPosition->update();
    destRect.x = _screenPosition->getX();
    destRect.y = _screenPosition->getY();
}


