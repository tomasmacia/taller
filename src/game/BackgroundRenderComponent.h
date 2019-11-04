
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
    //void renderInOwnWay() override;
    ToClientPack* generateRenderable() override;

private:
    float _parallaxSpeed;
};
#endif //BACKGROUND_RENDER_COMPONENT_H