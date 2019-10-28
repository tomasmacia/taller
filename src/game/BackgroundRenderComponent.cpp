#include "BackgroundRenderComponent.h"
#include "CameraComponent.h"
#include "Game.h"

#include <iostream>

BackgroundRenderComponent::BackgroundRenderComponent(Entity* camera, string string_path, float parallaxSpeed) {
    currentSprite = string_path;
    setCamera(camera);
    _parallaxSpeed = parallaxSpeed;
}

void BackgroundRenderComponent::init() {
    loadTexture();

    int screenResolutionWidth = _camera->getWindowWidth();
    int screenResolutionHeight = _camera->getWindowHeight();
    float aspectRatio = (float)(screenResolutionWidth)/(float)(screenResolutionHeight);

    destRect.w = screenResolutionWidth;
    destRect.h = screenResolutionHeight;
    destRect.x = 0;
    destRect.y = 0;

    srcRect.w = (int)(aspectRatio*(float)(texture.getHeight()));
    srcRect.h = texture.getHeight();
    srcRect.x = 0;
    srcRect.y = 0;

}

void BackgroundRenderComponent::update() {
    loadNextImage();
}

void BackgroundRenderComponent::renderInOwnWay() {
    texture.render(&srcRect, &destRect,false);
}

void BackgroundRenderComponent::loadNextImage(){

    int screenWidth = srcRect.w;
    int spriteWidth = texture.getWidth();

    int newX = ((float)spriteWidth*_camera->getLevelPercentageCovered()*_parallaxSpeed);

    if ((newX + screenWidth) < spriteWidth){
        srcRect.x = newX;
    }
}
