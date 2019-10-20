#include "BackgroundRenderComponent.h"
#include "CameraPositionComponent.h"
#include "Game.h"

#include <iostream>

BackgroundRenderComponent::BackgroundRenderComponent(string string_path,
                                             float parallaxSpeed) {
    currentSprite = string_path;
    _parallaxSpeed = parallaxSpeed;
}

void BackgroundRenderComponent::init() {
    loadTexture();

    int screenResolutionWidth = (int)(Game::getInstance().getConfig()->screenResolution.width);
    int screenResolutionHeight = (int)(Game::getInstance().getConfig()->screenResolution.height);

    float aspectRatio = (float)(screenResolutionWidth)/(float)(screenResolutionHeight);

    destRect.w = screenResolutionWidth;
    destRect.h = screenResolutionHeight;
    destRect.x = 0;
    destRect.y = 0;

    srcRect.w = (int)(aspectRatio*(float)(texture.getHeight()));
    srcRect.h = texture.getHeight();
    srcRect.x = 0;
    srcRect.y = 0;

}

void BackgroundRenderComponent::update() {
    loadNextImage();
}

void BackgroundRenderComponent::renderInOwnWay() {
    texture.render(&srcRect, &destRect,false);
}

void BackgroundRenderComponent::loadNextImage(){

    auto positionComponent = entity->getComponent<PositionComponent>();
    auto cameraPositionComponent = positionComponent->getCamera()->getComponent<CameraPositionComponent>();

    srcRect.x = (int)((float)(cameraPositionComponent->currentX)*_parallaxSpeed);
}

void BackgroundRenderComponent::loadErrorBackgroundImage(){
    texture.drawErrorColor();
}


