#include "BackgroundRenderComponent.h"
#include "CameraPositionComponent.h"
#include "Game.h"

BackgroundRenderComponent::BackgroundRenderComponent(std::vector<string> string_paths) {
    _string_paths = string_paths;
}

void BackgroundRenderComponent::init() {
    destRect.w = (int)(Game::getInstance().getConfig()->screenResolution.width);
    destRect.h = (int)(Game::getInstance().getConfig()->screenResolution.height);
    destRect.x = 0;
    destRect.y = 0;

    _imageCounter = 0;
    _imageAmount = _string_paths.size();
    currentSprite = _string_paths.at(_imageCounter);
    loadTexture();
}

void BackgroundRenderComponent::update() {
    updatePosition();
    loadNextImage();
}

void BackgroundRenderComponent::loadNextImage(){

    if (currentSpriteFinished()){
        _imageCounter++;
        if (_imageCounter >= _imageAmount){
            loadErrorBackgroundImage();
        }
        else{
            currentSprite = _string_paths.at(_imageCounter);
            loadTexture();
        }
    }
    else{
        auto positionComponent = entity->getComponent<PositionComponent>();
        auto cameraPositionComponent = positionComponent->getCamera()->getComponent<CameraPositionComponent>();

        srcRect.w = (int)(Game::getInstance().getConfig()->screenResolution.width);
        srcRect.h = (int)(Game::getInstance().getConfig()->screenResolution.height);
        srcRect.x = cameraPositionComponent->currentX;
        srcRect.y = 0;
    }
}

bool BackgroundRenderComponent::currentSpriteFinished(){
    return (srcRect.x + srcRect.w) >= texture.getWidth();
}

void BackgroundRenderComponent::loadErrorBackgroundImage(){
    texture.drawErrorColor();
}


