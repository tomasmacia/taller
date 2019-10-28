#include <string>
#include "NonMobileRenderComponent.h"
#include "GameServer.h"

#include <iostream>


NonMobileRenderComponent::NonMobileRenderComponent(Entity* camera, std::string string_path){
    currentSprite = string_path;
    setCamera(camera);
}

void NonMobileRenderComponent::init() {

    setDimentions();
    getCurrentSpriteDimentions();

    srcRect.w = currentSpriteWidth;
    srcRect.h = currentSpriteHight;
    srcRect.x = 0;
    srcRect.y = 0;    
}

void NonMobileRenderComponent::update() {
    updatePosition();
}

ToClientPack NonMobileRenderComponent::generateRenderable() {
    return ToClientPack(currentSprite,srcRect,destRect,false);
}

/*
void NonMobileRenderComponent::renderInOwnWay() {
    texture.render(&srcRect, &destRect,false);
}
*/