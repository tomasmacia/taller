
#ifndef CHARACTER_RENDER_COMPONENT_H
#define CHARACTER_RENDER_COMPONENT_H

#include "ECS.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "PositionComponent.h"
#include "../LogLib/LogManager.h"

class CharacterRenderComponent : public Component{

    public:
        CharacterRenderComponent(PositionComponent* iposition, std::string ispritePath, SDL_Renderer* irenderer);
        void update();
        void render();

    private:
        PositionComponent* position;
        std::string spritePath;
        SDL_Renderer* renderer;
        SDL_Texture* texture;
        SDL_Rect* srcRect;
        SDL_Rect* destRect;
};
#endif