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
    Appearance(ScreenPosition* screenPosition);

    virtual void update() = 0;
    virtual Renderable* generateRenderable();
    bool onScreen();

    void setTransparent();

    bool isTransparent();

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

    ScreenPosition* _screenPosition = nullptr;

    bool transparent = false;
    string TRANSPARENT_SPRITE = "path"; //todo
};
#endif //RENDER_COMPONENT_H