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
    return _screen->onScreen(destRect.x,destRect.y);
}

void Appearance::initDestRect(int w, int h){
    destRect.w = w;
    destRect.h = h;
    destRect.x = _position->getX();
    destRect.y = _position->getY();
}