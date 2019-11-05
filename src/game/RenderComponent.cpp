#include "GameServer.h"
#include "RenderComponent.h"
#include "CameraComponent.h"
#include "../utils/ImageUtils.h"

ToClientPack* RenderComponent::emitRenderable() {
    if (onScreen()){
        return generateRenderable();
    }
    else{
        return new ToClientPack(); //NULL PATTERN
    }
}

void RenderComponent::updatePosition(){
    auto positionComponent = entity->getComponent<PositionComponent>();

    destRect.x = positionComponent->getX() - _camera->currentX;
    destRect.y = positionComponent->getY();
}

bool RenderComponent::onScreen(){
    return _camera->onScreen(destRect.x,destRect.y);
}

void RenderComponent::setCamera(Entity* camera){
    _camera = camera->getComponent<CameraComponent>();
}

void RenderComponent::setDimentions(){
    destRect.w = (int)((float)(_camera->getWindowWidth())*WIDTH_SCALE);
    destRect.h = (int)((float)(_camera->getWindowHeight())*HEIGHT_SCALE);
    destRect.x = (int)entity->getComponent<PositionComponent>()->getX();
    destRect.y = (int)entity->getComponent<PositionComponent>()->getY();
}

void RenderComponent::getCurrentSpriteDimentions() {
    ImageSize imgSize = ImageUtils::getImageSize(currentSprite);
    currentSpriteWidth = imgSize.width;
    currentSpriteHight = imgSize.height;
    //TextureWrapper::measureWidthAndHeighthOf(currentSprite,&currentSpriteWidth,&currentSpriteHight);
}