//
// Created by Tomás Macía on 21/09/2019.
//

#include "GameObject.h"

GameObject::GameObject(const char *textureFile, int xPos, int yPos) {
    _physicsComponent = new PhysicsComponent(xPos,yPos);
    _graphicsComponent = new GraphicsComponent(textureFile);
}

//void GameObject::render() {
//    SDL_RenderCopy(Game::getInstance().getRenderer(), texture, &sourceRect, &destinationRect);
//}
