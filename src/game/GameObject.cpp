//
// Created by Tomás Macía on 21/09/2019.
//

#include "GameObject.h"

GameObject::GameObject(int xPos, int yPos, int width, int height) {
    _physicsComponent = new PhysicsComponent(xPos,yPos);
    _graphicsComponent = new GraphicsComponent(width,height,_physicsComponent);
}

//void GameObject::render() {
//    SDL_RenderCopy(Game::getInstance().getRenderer(), texture, &sourceRect, &destinationRect);
//}
