#include "BackgroundAppearance.h"

#include <utility>

BackgroundAppearance::BackgroundAppearance(Screen* screen, string string_path, float parallaxSpeed) {
    currentSprite = std::move(string_path);
    _parallaxSpeed = parallaxSpeed;
    _screen = screen;
    init();
}

void BackgroundAppearance::init() {

    int screenResolutionWidth = _screen->getWindowWidth();
    int screenResolutionHeight = _screen->getWindowHeight();
    float aspectRatio = (float)(screenResolutionWidth)/(float)(screenResolutionHeight);

    destRect.w = screenResolutionWidth;
    destRect.h = screenResolutionHeight;
    destRect.x = 0;
    destRect.y = 0;

    srcRect.w = (int)(aspectRatio*(float)(currentSpriteHeight));
    srcRect.h = currentSpriteHeight;
    srcRect.x = 0;
    srcRect.y = 0;
}

void BackgroundAppearance::update() {
    loadNextImage();
}

void BackgroundAppearance::loadNextImage(){

    int screenWidth = srcRect.w;
    int spriteWidth = currentSpriteWidth;

    int newX = ((float)spriteWidth*_screen->getLevelPercentageCovered()*_parallaxSpeed);

    if ((newX + screenWidth) < spriteWidth){
        srcRect.x = newX;
    }
}

Renderable *BackgroundAppearance::actuallyGenerateRenderable() {
    return new Renderable(currentSprite,srcRect,destRect,false);
}

