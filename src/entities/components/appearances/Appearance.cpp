#include "../../../game/GameServer.h"
#include "Appearance.h"
#include "../../Screen.h"
#include "../../../image/ImageUtils.h"

Renderable* Appearance::emitRenderable() {
    if (onScreen()){
        return generateRenderable();
    }
    else{
        return new Renderable(); //NULL PATTERN
    }
}

void Appearance::updatePosition(){
    auto positionComponent = entity->getComponent<Position>();

    destRect.x = positionComponent->getX() - _camera->currentX;
    destRect.y = positionComponent->getY();
}

bool Appearance::onScreen(){
    return _camera->onScreen(destRect.x,destRect.y);
}

void Appearance::setCamera(Entity* camera){
    _camera = camera->getComponent<Screen>();
}

void Appearance::setDimentions(){
    destRect.w = (int)((float)(_camera->getWindowWidth())*WIDTH_SCALE);
    destRect.h = (int)((float)(_camera->getWindowHeight())*HEIGHT_SCALE);
    destRect.x = (int)entity->getComponent<Position>()->getX();
    destRect.y = (int)entity->getComponent<Position>()->getY();
}

void Appearance::getCurrentSpriteDimentions() {
    ImageSize imgSize = ImageUtils::getImageSize(currentSprite);
    currentSpriteWidth = imgSize.width;
    currentSpriteHight = imgSize.height;
    //TextureWrapper::measureWidthAndHeighthOf(currentSprite,&currentSpriteWidth,&currentSpriteHight);
}