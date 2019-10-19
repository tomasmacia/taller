#include "BackgroundRenderComponent.h"
#include "CameraPositionComponent.h"
#include "Game.h"

#include <iostream>

BackgroundRenderComponent::BackgroundRenderComponent(string string_path,
                                             int parallaxSpeed) {
    currentSprite = string_path;
    _parallaxSpeed = parallaxSpeed;
}

void BackgroundRenderComponent::init() {
    destRect.w = (int)(Game::getInstance().getConfig()->screenResolution.width);
    destRect.h = (int)(Game::getInstance().getConfig()->screenResolution.height);
    destRect.x = 0;
    destRect.y = 0;

    srcRect.w = (int)(Game::getInstance().getConfig()->screenResolution.width);
    srcRect.h = (int)(Game::getInstance().getConfig()->screenResolution.height);
    srcRect.x = 0;
    srcRect.y = 0;

    loadTexture();
}

void BackgroundRenderComponent::update() {
    updatePosition();
    loadNextImage();
}

void BackgroundRenderComponent::render() {
    texture.render(&srcRect, &destRect,false);
    //std::cout<<currentSprite<<'\n';
}

void BackgroundRenderComponent::loadNextImage(){
    /*
    std::cout<<"_imageAmount: "<<_imageAmount<<'\n';
    std::cout<<"_imageCounter: "<<_imageCounter<<'\n';
    std::cout<<"currentSprite: "<<currentSprite<<'\n';
    std::cout<<"SpriteWidth: "<<texture.getWidth()<<'\n';
    std::cout<<"CameraStart: "<<srcRect.x<<'\n';
    std::cout<<"CameraEnd: "<<(srcRect.x + srcRect.w)<<'\n';
    std::cout<<"=============================: "<<'\n';
    std::cout<<'\n';*/

    auto positionComponent = entity->getComponent<PositionComponent>();
    auto cameraPositionComponent = positionComponent->getCamera()->getComponent<CameraPositionComponent>();

    srcRect.x = cameraPositionComponent->currentX*_parallaxSpeed;
}

void BackgroundRenderComponent::loadErrorBackgroundImage(){
    texture.drawErrorColor();
}


