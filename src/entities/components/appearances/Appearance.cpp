#include "Appearance.h"

Renderable* Appearance::generateRenderable() {
    if (onScreen()){
        return actuallyGenerateRenderable();
    }
    else{
        return nullptr;
    }
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