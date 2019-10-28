#include "BackgroundRenderComponent.h"
#include "CameraComponent.h"
#include "ToClientPack.h"

#include <iostream>

BackgroundRenderComponent::BackgroundRenderComponent(Entity* camera, string string_path, float parallaxSpeed) {
    currentSprite = string_path;
    setCamera(camera);
    _parallaxSpeed = parallaxSpeed;
}

void BackgroundRenderComponent::init() {
    getCurrentSpriteDimentions();

    int screenResolutionWidth = _camera->getWindowWidth();
    int screenResolutionHeight = _camera->getWindowHeight();
    float aspectRatio = (float)(screenResolutionWidth)/(float)(screenResolutionHeight);

    destRect.w = screenResolutionWidth;
    destRect.h = screenResolutionHeight;
    destRect.x = 0;
    destRect.y = 0;

    srcRect.w = (int)(aspectRatio*(float)(currentSpriteHight));
    srcRect.h = currentSpriteHight;
    srcRect.x = 0;
    srcRect.y = 0;

}

void BackgroundRenderComponent::update() {
    loadNextImage();
}

void BackgroundRenderComponent::loadNextImage(){

    int screenWidth = srcRect.w;
    int spriteWidth = currentSpriteWidth;

    int newX = ((float)spriteWidth*_camera->getLevelPercentageCovered()*_parallaxSpeed);

    if ((newX + screenWidth) < spriteWidth){
        srcRect.x = newX;
    }
}

ToClientPack BackgroundRenderComponent::generateRenderable() {
    return ToClientPack(currentSprite,srcRect,destRect,false);
}

/*
void BackgroundRenderComponent::renderInOwnWay() {
    texture.render(&srcRect, &destRect,false);
}
 */
