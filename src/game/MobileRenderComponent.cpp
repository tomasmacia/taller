#include "MobileRenderComponent.h"
#include "StateComponent.h"

void MobileRenderComponent::update() {

    auto state = entity->getComponent<StateComponent>();

    if (state->changed()){
        handleIncomingAction();
        getCurrentSpriteDimentions();
        _imageCounter = 0;
    }
    updatePosition();
    loadNextImage();
}

void MobileRenderComponent::loadNextImage(){

    srcRect.w = currentSpriteWidth/_imageAmount;
    srcRect.h = currentSpriteHight;
    srcRect.x = srcRect.w * (int)(_imageCounter / DELAY);
    srcRect.y = 0;

    _imageCounter++;
    
    if (_imageCounter == (_imageAmount *DELAY))
        entity->getComponent<StateComponent>()->setFinished();

    _imageCounter = _imageCounter % (_imageAmount * DELAY);
}

bool MobileRenderComponent::isFliped() {
    return entity->getComponent<StateComponent>()->isFliped();
}

void MobileRenderComponent::flip() {
    entity->getComponent<StateComponent>()->setFliped();
}

ToClientPack MobileRenderComponent::generateRenderable() {
    return ToClientPack(currentSprite,srcRect,destRect,isFliped());
}

/*
void MobileRenderComponent::renderInOwnWay() {
    texture.render(&srcRect, &destRect,isFlipped());
}
 */


