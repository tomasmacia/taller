#include "CharacterRenderComponent.h"
#include "Game.h"

CharacterRenderComponent::CharacterRenderComponent(std::string ispritePath) {
    this->spritePath = ispritePath;
    this->destRect = new SDL_Rect();
    this->destRect->w = 57;
    this->destRect->h = 125;

    SDL_Surface* loadedSurface = IMG_Load(spritePath.c_str());
    if ( loadedSurface == NULL ) {
        LogManager::logError("Unable to load image, SDL_image Error:");
    } else {
        texture = SDL_CreateTextureFromSurface(Game::getInstance().getRenderer(), loadedSurface);
        if( texture == NULL ) {
            LogManager::logError( "Unable to create texture from, SDL Error:");
        }
        SDL_FreeSurface( loadedSurface );
    }

    

};

void CharacterRenderComponent::update() {
    auto &positionComponent = entity->getComponent<PositionComponent>();

    destRect->x = positionComponent.getX();
    destRect->y = positionComponent.getY();
};

void CharacterRenderComponent::render() {
    SDL_RenderCopy(Game::getInstance().getRenderer(),texture,NULL,destRect);
};
