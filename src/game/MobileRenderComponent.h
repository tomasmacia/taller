
#ifndef _MOBILE_RENDER_COMPONENT_H
#define _MOBILE_RENDER_COMPONENT_H

#include "RenderComponent.h"

class MobileRenderComponent : public RenderComponent {
public:
    void update() override;
    void render() override;

    ~MobileRenderComponent() override;

    virtual int getJumpDuration() = 0;
    
protected:
    virtual void handleIncomingAction() = 0;
    void loadNextImage() override;
    bool isFlipped();
    void flip();

    int DELAY;
};
#endif //_MOBILE_RENDER_COMPONENT_H