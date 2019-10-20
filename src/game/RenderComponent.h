#ifndef RENDER_COMPONENT_H
#define RENDER_COMPONENT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "ECS.h"
#include "Action.h"
#include "PositionComponent.h"
#include "../LogLib/LogManager.h"
#include "TextureWrapper.h"

class RenderComponent : public Component {
public:
    virtual void update() = 0;
    void render();

    ~RenderComponent() override;
    
protected:
    virtual void loadNextImage() = 0;
    virtual void renderInOwnWay() = 0;

    bool onScreen();
    void updatePosition();
    void loadTexture();

    TextureWrapper texture;
    SDL_Rect srcRect;
    SDL_Rect destRect;

    int _imageAmount;
    int _imageCounter = 0;

    std::string currentSprite;
};
#endif //RENDER_COMPONENT_H