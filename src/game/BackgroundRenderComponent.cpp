#include "BackgroundRenderComponent.h"
#include "CameraPositionComponent.h"
#include "Game.h"

#include <iostream>

BackgroundRenderComponent::BackgroundRenderComponent(std::vector<string> string_paths,
                                             int parallaxSpeed) {
    _string_paths = string_paths;
    _parallaxSpeed = parallaxSpeed;
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

void BackgroundRenderComponent::render() {
    texture.render(&srcRect, &destRect,false);
}

void BackgroundRenderComponent::loadNextImage(){

    if (currentSpriteFinished()){
        std::cout<<"currentSprite: "<<currentSprite<<'\n';
        std::cout<<"width: "<<texture.getWidth()<<'\n';
        std::cout<<"_imageCounter: "<<_imageCounter<<'\n';
        std::cout<<"_imageAmount: "<<_imageAmount<<'\n';
        std::cout<<"=============================: "<<'\n';
        std::cout<<'\n';
        _imageCounter++;
        _imageCounter = _imageCounter % _imageAmount ;

        /*
        if (_imageCounter >= _imageAmount){
            loadErrorBackgroundImage();
        }
        else{
            currentSprite = _string_paths.at(_imageCounter);
            loadTexture();
        }*/

    }
    else{
        auto positionComponent = entity->getComponent<PositionComponent>();
        auto cameraPositionComponent = positionComponent->getCamera()->getComponent<CameraPositionComponent>();

        srcRect.w = (int)(Game::getInstance().getConfig()->screenResolution.width);
        srcRect.h = (int)(Game::getInstance().getConfig()->screenResolution.height);
        srcRect.x = cameraPositionComponent->currentX*_parallaxSpeed;
        srcRect.y = 0;
    }
}

bool BackgroundRenderComponent::currentSpriteFinished(){
    return (srcRect.x + srcRect.w) >= texture.getWidth();
}

void BackgroundRenderComponent::loadErrorBackgroundImage(){
    texture.drawErrorColor();
}


