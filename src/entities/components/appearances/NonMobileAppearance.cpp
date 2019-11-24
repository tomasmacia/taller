#include <string>
#include "NonMobileAppearance.h"
#include "../../../game/GameServer.h"

#include <iostream>


NonMobileAppearance::NonMobileAppearance(Entity* camera, std::string string_path){
    currentSprite = string_path;
    setCamera(camera);
}

void NonMobileAppearance::init() {

    setDimentions();
    getCurrentSpriteDimentions();

    srcRect.w = currentSpriteWidth;
    srcRect.h = currentSpriteHight;
    srcRect.x = 0;
    srcRect.y = 0;    
}

void NonMobileAppearance::update() {
    updatePosition();
}

Renderable* NonMobileAppearance::generateRenderable() {
    return new Renderable(currentSprite, srcRect, destRect, false);
}

/*
void NonMobileAppearance::renderInOwnWay() {
    texture.render(&srcRect, &destRect,false);
}
*/