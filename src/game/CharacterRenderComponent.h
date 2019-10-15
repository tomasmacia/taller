
#ifndef CHARACTER_RENDER_COMPONENT_H
#define CHARACTER_RENDER_COMPONENT_H

#include "ECS.h"
#include <SDL2/SDL.h>
#include "PositionComponent.h"

class CharacterRenderComponent : public Component{

    public:
        CharacterRenderComponent(PositionComponent iplayerPos, std::string ispritePath, SDL_Renderer irenderer);
        void update();
        void render();

    private:
        PositionComponent playerPos;
        std::string spritePath;
        SDL_Renderer renderer;

};
#endif