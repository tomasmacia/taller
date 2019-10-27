
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

    Action _action = NONE;
    int imageAmount = 1; //NO DEBERIA ESTA HARDCODEADO. DEBERIA DEPENDER DE LA ACTION
    int actionCount = 1;

    void loadTexture();
    void switchAction(Action);
    void loadNextImage();

    bool isFlipped() {
        return flipped;
    }

    void flip() {
        flipped = true;
    }

    bool flipped = false;

    std::string currentSprite;
};
#endif