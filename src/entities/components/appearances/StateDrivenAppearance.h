
#ifndef _MOBILE_RENDER_COMPONENT_H
#define _MOBILE_RENDER_COMPONENT_H

#include "Appearance.h"
#include "../ScreenPosition.h"

class StateDrivenAppearance : public Appearance {
public:
    StateDrivenAppearance(ScreenPosition* screenPosition, State* state);

    void update() override ;
    Renderable* generateRenderable() override ;

    bool isFliped();

    virtual ~StateDrivenAppearance() {};

protected:
    virtual void handleCurrentState() = 0;
    virtual void init() = 0;

    Renderable* actuallyGenerateRenderable() override;
    void loadNextImage() override;
    void updateDestRectPosition();

    int _imageAmount;
    int _imageCounter = 0;

    int DELAY;

    ScreenPosition* _screenPosition = nullptr;
    State* _state = nullptr;
};
#endif //_MOBILE_RENDER_COMPONENT_H