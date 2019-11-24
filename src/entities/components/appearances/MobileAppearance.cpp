#include "MobileAppearance.h"
#include "../State.h"

void MobileAppearance::update() {

    auto state = entity->getComponent<State>();

    if (state->changed()){
        handleIncomingAction();
        getCurrentSpriteDimentions();
        _imageCounter = 0;
    }
    updatePosition();
    loadNextImage();
}

void MobileAppearance::loadNextImage(){

    srcRect.w = currentSpriteWidth/_imageAmount;
    srcRect.h = currentSpriteHight;
    srcRect.x = srcRect.w * (int)(_imageCounter / DELAY);
    srcRect.y = 0;

    _imageCounter++;
    
    if (_imageCounter == (_imageAmount * DELAY))
        entity->getComponent<State>()->setFinished();

    _imageCounter = _imageCounter % (_imageAmount * DELAY);
}

bool MobileAppearance::isFliped() {
    return entity->getComponent<State>()->isFliped();
}

void MobileAppearance::flip() {
    entity->getComponent<State>()->setFliped();
}

Renderable* MobileAppearance::generateRenderable() {
    return new Renderable(currentSprite, srcRect, destRect, isFliped());
}

/*
void MobileAppearance::renderInOwnWay() {
    texture.render(&srcRect, &destRect,isFlipped());
}
 */


