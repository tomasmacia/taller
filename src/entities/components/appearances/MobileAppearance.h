
#ifndef _MOBILE_RENDER_COMPONENT_H
#define _MOBILE_RENDER_COMPONENT_H

#include "Appearance.h"

class MobileAppearance : public Appearance {
public:
    void update() override;

    virtual int getJumpDuration() = 0;
    
protected:
    virtual void handleIncomingAction() = 0;
    Renderable* generateRenderable() override;
    //void renderInOwnWay() override;

    void loadNextImage() override;
    bool isFliped();
    void flip();

    int DELAY;
};
#endif //_MOBILE_RENDER_COMPONENT_H