
#ifndef BACKGROUND_RENDER_COMPONENT_H
#define BACKGROUND_RENDER_COMPONENT_H

#include "RenderComponent.h"
#include <vector>

class BackgroundRenderComponent : public RenderComponent {
public:
    BackgroundRenderComponent(std::vector<string> string_paths);
    void init() override;

private:
    std::vector<string> _string_paths;
};
#endif //BACKGROUND_RENDER_COMPONENT_H