
#ifndef RENDER_COMPONENT_H
#define RENDER_COMPONENT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "ECS.h"
#include "Action.h"
#include "PositionComponent.h"
#include "../LogLib/LogManager.h"
#include "../parser/config/characterxml.h"
#include "TextureWrapper.h"
#include "StateComponent.h"

class RenderComponent : public Component {
public:
    void update() override;
    void render() override;

    ~RenderComponent() override;

    virtual int getJumpDuration(){}
    
protected:
    virtual void handleIncomingAction(){}
    virtual void loadNextImage();

    TextureWrapper texture;
    SDL_Rect srcRect;
    SDL_Rect destRect;

    int DELAY;
    int _imageAmount;
    int _imageCounter = 0;

    std::string currentSprite;

    void loadTexture();
    void updatePosition();

    virtual bool isFlipped() {
        return entity->getComponent<StateComponent>()->isFlipped();
    }

    void flip() {
        entity->getComponent<StateComponent>()->setFliped();
    }
};
#endif //RENDER_COMPONENT_H