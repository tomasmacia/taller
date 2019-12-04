#include "StateDrivenAppearance.h"

StateDrivenAppearance::StateDrivenAppearance(ScreenPosition* screenPosition, State *state) : Appearance(screenPosition){
    _screenPosition = screenPosition;
    _state = state;
}

Renderable* StateDrivenAppearance::generateRenderable() {

    if (onScreen()){
        return actuallyGenerateRenderable();
    }
    else{
        return nullptr;
    }
}

void StateDrivenAppearance::update() {

    if (!isTransparent()){
        handleCurrentState();
    }
    loadNextImage();
    updateDestRectPosition();
}

void StateDrivenAppearance::loadNextImage(){

    srcRect.w = currentSpriteWidth/_imageAmount;
    srcRect.h = currentSpriteHeight;
    srcRect.x = srcRect.w * (int)(_imageCounter / DELAY);
    srcRect.y = 0;

    _imageCounter++;

    if (_imageCounter == (_imageAmount * DELAY)){
        _state->setFinished();
        _imageCounter = 0;
    }

    _imageCounter = _imageCounter % (_imageAmount * DELAY);
}

Renderable *StateDrivenAppearance::actuallyGenerateRenderable() {
    return new Renderable(currentSprite,srcRect,destRect,isFliped());
}

void StateDrivenAppearance::updateDestRectPosition(){

    _screenPosition->update();
    destRect.x = _screenPosition->getX();
    destRect.y = _screenPosition->getY();
}

bool StateDrivenAppearance::isFliped() {
    return _state->isFliped();
}