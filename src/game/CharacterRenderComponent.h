
#ifndef CHARACTER_RENDER_COMPONENT_H
#define CHARACTER_RENDER_COMPONENT_H

#include "ECS.h"
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include "PositionComponent.h"
#include "../LogLib/LogManager.h"

class CharacterRenderComponent : public Component{

    public:
        CharacterRenderComponent(std::string ispritePath);
        void update() override;
        void render() override;


    private:
        std::string spritePath;
        SDL_Renderer* renderer;
        SDL_Texture* texture;
        SDL_Rect* srcRect;
        SDL_Rect* destRect;
};
#endif