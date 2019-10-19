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

    float ratioAspect = (float)(screenResolutionWidth)/(float)(screenResolutionHeight);

    destRect.w = screenResolutionWidth;
    destRect.h = screenResolutionHeight;
    destRect.x = 0;
    destRect.y = 0;

    srcRect.w = (int)(ratioAspect*(float)(texture.getHeight()));
    srcRect.h = texture.getHeight();
    srcRect.x = 0;
    srcRect.y = 0;

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

    srcRect.x = (int)((float)(cameraPositionComponent->currentX)*_parallaxSpeed);
}

void BackgroundRenderComponent::loadErrorBackgroundImage(){
    texture.drawErrorColor();
}


