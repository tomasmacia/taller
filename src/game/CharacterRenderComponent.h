
#ifndef CHARACTER_RENDER_COMPONENT_H
#define CHARACTER_RENDER_COMPONENT_H

#include "ECS.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Action.h"
#include "PositionComponent.h"
#include "../LogLib/LogManager.h"
#include "../parser/config/characterxml.h"
#include "TextureWrapper.h"
#include "StateComponent.h"

class CharacterRenderComponent : public Component {
public:
    CharacterRenderComponent(CharacterXML *characterConfig);
    void update() override;
    void render() override;
    void init() override;

    ~CharacterRenderComponent() override;

private:
    CharacterXML characterConfig;
    TextureWrapper texture;
    SDL_Rect srcRect;
    SDL_Rect destRect;

    int STAND_IMAGE_AMOUNT = 1;
    int WALK_IMAGE_AMOUNT = 9;
    int JUMP_IMAGE_AMOUNT = 13;
    int PUNCH_IMAGE_AMOUNT = 3;
    int KICK_IMAGE_AMOUNT = 6;
    int JUMP_KICK_IMAGE_AMOUNT = 13;
    int CROUCH_IMAGE_AMOUNT = 4;

    int DELAY = 7;
    int _imageAmount = 1;
    int _imageCounter = 0;

    void updatePosition();
    void loadTexture();
    void handleIncomingAction();
    void loadNextImage();

    bool isFlipped() {
        return entity->getComponent<StateComponent>()->isFlipped();
    }

    void flip() {
        entity->getComponent<StateComponent>()->setFliped();
    }

    std::string currentSprite;
};
#endif