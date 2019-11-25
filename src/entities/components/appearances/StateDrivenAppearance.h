
#ifndef _MOBILE_RENDER_COMPONENT_H
#define _MOBILE_RENDER_COMPONENT_H

#include "Appearance.h"

class StateDrivenAppearance : public Appearance {
public:
    void update() override ;

protected:
    virtual void handleCurrentState() = 0;
    virtual void init() = 0;

    Renderable* actuallyGenerateRenderable() override;
    void loadNextImage() override;

    bool isFliped();

    int DELAY{};
};
#endif //_MOBILE_RENDER_COMPONENT_H