#include "CharacterRenderComponent.h"

CharacterRenderComponent::CharacterRenderComponent(PositionComponent* iposition, std::string ispritePath, SDL_Renderer* irenderer){
    this->position = iposition;
    this->spritePath = ispritePath;
    this->renderer = irenderer;
    this->destRect = new SDL_Rect();
    this->destRect->w = 57;
    this->destRect->h = 125;

    SDL_Surface* loadedSurface = IMG_Load(spritePath.c_str());
    if( loadedSurface == NULL )
    {
        LogManager::logError("Unable to load image, SDL_image Error:");
    }
    else
    {
        texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if( texture == NULL )
        {
            LogManager::logError( "Unable to create texture from, SDL Error:");
        }
        SDL_FreeSurface( loadedSurface );
    };

    

};

void CharacterRenderComponent::update(){
    destRect->x = position->getX();
    destRect->y = position->getY();
};

void CharacterRenderComponent::render(){
    SDL_RenderCopy(renderer,texture,NULL,destRect);
};
