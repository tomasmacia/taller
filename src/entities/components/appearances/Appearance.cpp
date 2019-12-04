#include "Appearance.h"

Appearance::Appearance(ScreenPosition *screenPosition) {
    _screenPosition = screenPosition;
}

Renderable *Appearance::generateRenderable() {
    return actuallyGenerateRenderable();
}

void Appearance::getCurrentSpriteDimentions() {
    ImageSize imgSize = ImageUtils::getImageSize(currentSprite);
    currentSpriteWidth = imgSize.width;
    currentSpriteHeight = imgSize.height;
}

bool Appearance::onScreen(){
    return _screenPosition->onScreen();
}

void Appearance::initDestRect(int w, int h){
    destRect.w = w;
    destRect.h = h;
    destRect.x = _screenPosition->getX();
    destRect.y = _screenPosition->getY();
}

void Appearance::setTransparent() {

    currentSprite = TRANSPARENT_SPRITE;

    transparent = true;
}

bool Appearance::isTransparent() {
    return transparent;
}

