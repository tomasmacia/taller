#include <string>
#include "NonMobileRenderComponent.h"
#include "Game.h"

#include <iostream>


NonMobileRenderComponent::NonMobileRenderComponent(Entity* camera, std::string string_path){
    currentSprite = string_path;
    setCamera(camera);
}

void NonMobileRenderComponent::init() {

    setDimentions();
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
