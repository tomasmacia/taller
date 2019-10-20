#include "MobileRenderComponent.h"
#include "StateComponent.h"

void MobileRenderComponent::update() {

    auto state = entity->getComponent<StateComponent>();

    if (state->changed()){
        handleIncomingAction();
        loadTexture();
        _imageCounter = 0;
    }
    updatePosition();
    loadNextImage();
}

void MobileRenderComponent::renderInOwnWay() {
    texture.render(&srcRect, &destRect,isFlipped());
}

void MobileRenderComponent::loadNextImage(){

    srcRect.w = texture.getWidth()/_imageAmount;
    srcRect.h = texture.getHeight();
    srcRect.x = srcRect.w * (int)(_imageCounter / DELAY);
    srcRect.y = 0;

    _imageCounter++;
    
    if (_imageCounter == (_imageAmount *DELAY))
        entity->getComponent<StateComponent>()->setFinished();

    _imageCounter = _imageCounter % (_imageAmount * DELAY);
}

bool MobileRenderComponent::isFlipped() {
    return entity->getComponent<StateComponent>()->isFlipped();
}

void MobileRenderComponent::flip() {
    entity->getComponent<StateComponent>()->setFliped();
}


