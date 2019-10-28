
#ifndef BACKGROUND_RENDER_COMPONENT_H
#define BACKGROUND_RENDER_COMPONENT_H

#include <vector>
#include <string>
#include "RenderComponent.h"


class BackgroundRenderComponent : public RenderComponent {
public:
    BackgroundRenderComponent(Entity* camera, std::string string_path, float parallaxSpeed);
    void init() override;
    void update() override;

protected:
    void loadNextImage() override;
    void renderInOwnWay() override;

private:
    float _scaleFactor;
    float _parallaxSpeed;
};
#endif //BACKGROUND_RENDER_COMPONENT_H