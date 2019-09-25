//
// Created by Tomás Macía on 21/09/2019.
//

#include "GameObject.h"
#include "TextureManager.h"
#include "game.h"

GameObject::GameObject(const char *textureFile, int xPos, int yPos) {
    x = xPos;
    y = yPos;
    texture = TextureManager::loadTexture(textureFile);
}

void GameObject::render() {
    SDL_RenderCopy(Game::getInstance().getRenderer(), texture, &sourceRect, &destinationRect);
}
