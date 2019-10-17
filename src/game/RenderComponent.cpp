#include "Game.h"
#include "RenderComponent.h"
#include "StateComponent.h"
#include "CameraPositionComponent.h"

#include <iostream>

void RenderComponent::update() {

    auto state = entity->getComponent<StateComponent>();

    if (state->changed()){
        handleIncomingAction();
        loadTexture();
        _imageCounter = 0;
    }
    updatePosition();
    loadNextImage();
}

void RenderComponent::render() {
    texture.render(&srcRect, &destRect,isFlipped());
}


RenderComponent::~RenderComponent() {
    texture.free();
}

void RenderComponent::loadTexture() {
    texture.setWidthAndHeight(destRect.w, destRect.h);
    texture.loadFromFile(currentSprite);
}

void RenderComponent::loadNextImage(){

    srcRect.w = texture.getWidth()/_imageAmount;
    srcRect.h = texture.getHeight();
    srcRect.x = srcRect.w * (int)(_imageCounter / DELAY);
    srcRect.y = 0;

    /*
    std::cout << "sprite: "<< _imageCounter / DELAY <<"\n";
    std::cout << "_imageCounter: "<< _imageCounter <<"\n";
    std::cout << "_imageAmount: "<< _imageAmount <<"\n";
    std::cout << "currentSprite: "<< currentSprite <<"\n";
    std::cout << "============================\n";
    std::cout << "\n";*/

    _imageCounter++;
    
    if (_imageCounter == (_imageAmount *DELAY))
        entity->getComponent<StateComponent>()->setFinished();

    _imageCounter = _imageCounter % (_imageAmount * DELAY);
}

void RenderComponent::updatePosition(){
    auto positionComponent = entity->getComponent<PositionComponent>();
    auto cameraPositionComponent = positionComponent->getCamera()->getComponent<CameraPositionComponent>();

    destRect.x = positionComponent->getX() - cameraPositionComponent->currentX;
    destRect.y = positionComponent->getY();
}


