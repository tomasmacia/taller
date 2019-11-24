
#ifndef NON_MOBILE_RENDER_COMPONENT_H
#define NON_MOBILE_RENDER_COMPONENT_H

#include <string>
#include "Appearance.h"

class NonMobileAppearance : public Appearance {
public:
    NonMobileAppearance(Entity* camera, std::string string_path);

    void update() override;
    void init() override;

protected:
    void loadNextImage() override{} //Como es non moving no tiene next image
    Renderable* generateRenderable() override;
    //void renderInOwnWay() override;
};
#endif //NON_MOBILE_RENDER_COMPONENT_H