//
// Created by Tomás Macía on 21/09/2019.
//

#include "GameObject.h"
#include "TextureManager.h"
#include "Game.h"

GameObject::GameObject(const char *textureFile, int xPos, int yPos) {
    x = xPos;
    y = yPos;
    texture = TextureManager::loadTexture(textureFile);
}

void GameObject::update() {

    sourceRect.h = 32;
    sourceRect.w = 32;
    sourceRect.x = 0;
    sourceRect.y = 0;

    destinationRect.x = x;
    destinationRect.y = y;
    destinationRect.w = sourceRect.w * 2;
    destinationRect.h = sourceRect.h * 2;

}

void GameObject::render() {
    SDL_RenderCopy(Game::getInstance()->getRenderer(), texture, &sourceRect, &destinationRect);
}

