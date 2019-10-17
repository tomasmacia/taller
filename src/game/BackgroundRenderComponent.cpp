#include "BackgroundRenderComponent.h"
#include "Game.h"

BackgroundRenderComponent::BackgroundRenderComponent(std::vector<string> string_paths) {
    _string_paths = string_paths;
}

void BackgroundRenderComponent::init() {
    destRect.w = (int)(Game::getInstance().getConfig()->screenResolution.width * 0.2);
    destRect.h = (int)(Game::getInstance().getConfig()->screenResolution.height * 0.50);
    destRect.x = (int)(Game::getInstance().getConfig()->screenResolution.width * 0.3);
    destRect.y = (int)(Game::getInstance().getConfig()->screenResolution.height * 0.3);

    DELAY = 1;
    _imageAmount  = 1;  //PONER BIEN
    loadTexture();
    _imageCounter = 0;
}


