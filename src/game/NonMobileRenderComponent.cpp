#include <string>
#include "NonMobileRenderComponent.h"
#include "Game.h"

NonMobileRenderComponent::NonMobileRenderComponent(std::string string_path){
    currentSprite = string_path;
}

void NonMobileRenderComponent::init() {
    destRect.w = (int)(Game::getInstance().getConfig()->screenResolution.width * 0.2);
    destRect.h = (int)(Game::getInstance().getConfig()->screenResolution.height * 0.50);
    destRect.x = (int)(Game::getInstance().getConfig()->screenResolution.width * 0.3);
    destRect.y = (int)(Game::getInstance().getConfig()->screenResolution.height * 0.3);

    loadTexture();
}

void NonMobileRenderComponent::update() {
    updatePosition();
}

void NonMobileRenderComponent::renderInOwnWay() {
    texture.render(&srcRect, &destRect,false);
}
