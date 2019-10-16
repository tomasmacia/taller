#include "CharacterRenderComponent.h"
#include "CameraPositionComponent.h"
#include "Game.h"

CharacterRenderComponent::CharacterRenderComponent(CharacterXML *characterConfig) {
    this->characterConfig = *characterConfig;
}

void CharacterRenderComponent::init() {
    destRect.w = (int)(Game::getInstance().getConfig()->screenResolution.width * 0.2);
    destRect.h = (int)(Game::getInstance().getConfig()->screenResolution.height * 0.50);
    destRect.x = (int)(Game::getInstance().getConfig()->screenResolution.width * 0.3);
    destRect.y = (int)(Game::getInstance().getConfig()->screenResolution.height * 0.3);

    currentSprite = characterConfig.stand;

    loadTexture();
}

void CharacterRenderComponent::update() {
    auto positionComponent = entity->getComponent<PositionComponent>();
    auto cameraPositionComponent = positionComponent->getCamera()->getComponent<CameraPositionComponent>();

    destRect.x = positionComponent->getX() - cameraPositionComponent->currentX;
    destRect.y = positionComponent->getY();

    loadNextImage();
}

void CharacterRenderComponent::render() {
    texture.render(destRect.x, destRect.y);
}


CharacterRenderComponent::~CharacterRenderComponent() {
    texture.free();
}

void CharacterRenderComponent::loadTexture() {
    texture.setWidthAndHeight(destRect.w, destRect.h);
    texture.loadFromFile(currentSprite);
}

void CharacterRenderComponent::switchAction(Action action){

    if (_action ==  NONE) {  //si hay una accion que no es NONE no se cambia
        _action = action;
        switch (action) {
            case UP:
                currentSprite = characterConfig.walk;
                break;
            case DOWN:
                currentSprite = characterConfig.walk;
                break;
            case LEFT:
                if (!isFlipped()) flip();
                currentSprite = characterConfig.walk;
                break;
            case RIGHT:
                if (!isFlipped()) flip();
                currentSprite = characterConfig.walk;
                break;
            case JUMP:
                currentSprite = characterConfig.jump;
                break;
            case PUNCH:
                currentSprite = characterConfig.punch;
                break;
            case KICK:
                currentSprite = characterConfig.kick;
                break;
            case JUMP_KICK:
                currentSprite = characterConfig.jumpkick;
                break;
            case CROUCH:
                currentSprite = characterConfig.crouch;
                break;
            default:
                LogManager::logError("Default Render Switch Action"); // TODO poner un log mejor
                break;
        }
    }
}




void CharacterRenderComponent::loadNextImage() {
//    int width, height;
//    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
//
//    srcRect.h = height;
//    srcRect.w = width/imageAmount;
//    srcRect.x = ((int)(width/imageAmount)) * actionCount;
//    srcRect.y = height;
}


