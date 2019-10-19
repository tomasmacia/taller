#include "Game.h"
#include "RenderComponent.h"
#include "CameraPositionComponent.h"

#include <iostream>

RenderComponent::~RenderComponent() {
    texture.free();
}

void RenderComponent::loadTexture() {
    texture.setWidthAndHeight(destRect.w, destRect.h);
    texture.loadFromFile(currentSprite);
}

void RenderComponent::updatePosition(){
    auto positionComponent = entity->getComponent<PositionComponent>();
    auto cameraPositionComponent = positionComponent->getCamera()->getComponent<CameraPositionComponent>();

    destRect.x = positionComponent->getX() - cameraPositionComponent->currentX;
    destRect.y = positionComponent->getY();
}
