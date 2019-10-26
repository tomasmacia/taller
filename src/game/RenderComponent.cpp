#include "Game.h"
#include "RenderComponent.h"
#include "CameraPositionComponent.h"


RenderComponent::~RenderComponent() {
    texture.free();
}

void RenderComponent::render() {
    if (onScreen())
        renderInOwnWay();
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

bool RenderComponent::onScreen(){
    auto *camera = entity->getComponent<PositionComponent>()->getCamera()->getComponent<CameraPositionComponent>();
    return camera->onScreen(destRect.x,destRect.y);
}
