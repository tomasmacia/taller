#ifndef RENDER_COMPONENT_H
#define RENDER_COMPONENT_H

#include <string>
#include "../../../enumerates/Action.h"
#include "../../../image/ImageUtils.h"
#include "../../../net/messaging/Renderable.h"
#include "../../../image/Rect.h"
#include "../State.h"
#include "../ScreenPosition.h"

using namespace std;

class Appearance {

public:
    virtual void update() = 0;

    Renderable* generateRenderable();
    bool onScreen();

protected:
    virtual Renderable* actuallyGenerateRenderable() = 0;
    virtual void loadNextImage() = 0;

    void initDestRect(int w, int h);
    void getCurrentSpriteDimentions();

    int currentSpriteWidth;
    int currentSpriteHeight;

    Rect srcRect;
    Rect destRect;

    string currentSprite;

    State* _state = nullptr;
    ScreenPosition* _screenPosition = nullptr;

    float WIDTH_SCALE{};
    float HEIGHT_SCALE{};
};
#endif //RENDER_COMPONENT_H