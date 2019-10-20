
#ifndef NON_MOBILE_RENDER_COMPONENT_H
#define NON_MOBILE_RENDER_COMPONENT_H

#include <string>
#include "RenderComponent.h"

class NonMobileRenderComponent : public RenderComponent {
public:
    NonMobileRenderComponent(std::string string_path);

    void update() override;
    void init() override;

protected:
    void loadNextImage() override{} //Como es non moving no tiene next image
    void renderInOwnWay() override;
};
#endif //NON_MOBILE_RENDER_COMPONENT_H