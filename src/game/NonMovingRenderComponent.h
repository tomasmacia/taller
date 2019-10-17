
#ifndef NON_MOVING_RENDER_COMPONENT_H
#define NON_MOVING_RENDER_COMPONENT_H

#include "RenderComponent.h"

class NonMovingRenderComponent : public RenderComponent {
public:
    NonMovingRenderComponent(std::string string_path);
    void init() override;
};
#endif //NON_MOVING_RENDER_COMPONENT_H