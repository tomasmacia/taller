#include <string>
#include "NonMobileRenderComponent.h"
#include "Game.h"

#include <iostream>


NonMobileRenderComponent::NonMobileRenderComponent(std::string string_path){
    currentSprite = string_path;
}

void NonMobileRenderComponent::init() {
    destRect.w = (int)((float)(Game::getInstance().getConfig()->screenResolution.width)*WIDTH_SCALE);
    destRect.h = (int)((float)(Game::getInstance().getConfig()->screenResolution.height)*HEIGHT_SCALE);
    destRect.x = (int)entity->getComponent<PositionComponent>()->getX();
    destRect.y = (int)entity->getComponent<PositionComponent>()->getY();

    loadTexture();

    srcRect.w = (int)(texture.getWidth());
    srcRect.h = (int)(texture.getHeight());
    srcRect.x = 0;
    srcRect.y = 0;    
}

void NonMobileRenderComponent::update() {
    updatePosition();
}

void NonMobileRenderComponent::renderInOwnWay() {
    texture.render(&srcRect, &destRect,false);
}
