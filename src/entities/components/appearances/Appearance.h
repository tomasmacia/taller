#ifndef RENDER_COMPONENT_H
#define RENDER_COMPONENT_H

#include "../../../enumerates/Action.h"

class Appearance {
public:
    virtual void update() = 0;



protected:
    virtual void loadNextImage() = 0;
    virtual Renderable* generateRenderable() = 0;
    //virtual void renderInOwnWay() = 0;

    void getCurrentSpriteDimentions();
    bool onScreen();
    void updatePosition();
    void setCamera(Entity* camera);
    void setDimentions();

    int currentSpriteWidth;
    int currentSpriteHight;
    SDL_Rect srcRect;
    SDL_Rect destRect;

    CameraComponent* _camera = nullptr;

    float WIDTH_SCALE = 0.2;
    float HEIGHT_SCALE = 0.5;

    int _imageAmount;
    int _imageCounter = 0;

    std::string currentSprite;
};
#endif //RENDER_COMPONENT_H