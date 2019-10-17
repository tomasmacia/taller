#include "NonMovingRenderComponent.h"
#include "Game.h"

NonMovingRenderComponent::NonMovingRenderComponent(std::string string_path) {
    currentSprite = string_path;
}

void NonMovingRenderComponent::init() {
    destRect.w = (int)(Game::getInstance().getConfig()->screenResolution.width * 0.2);
    destRect.h = (int)(Game::getInstance().getConfig()->screenResolution.height * 0.50);
    destRect.x = (int)(Game::getInstance().getConfig()->screenResolution.width * 0.3);
    destRect.y = (int)(Game::getInstance().getConfig()->screenResolution.height * 0.3);

    DELAY = 1;
    _imageAmount  = 1;
    loadTexture();
    _imageCounter = 0;
}


