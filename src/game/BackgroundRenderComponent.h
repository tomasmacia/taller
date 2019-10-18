
#ifndef BACKGROUND_RENDER_COMPONENT_H
#define BACKGROUND_RENDER_COMPONENT_H

#include <vector>
#include <string>
#include "RenderComponent.h"


class BackgroundRenderComponent : public RenderComponent {
public:
    BackgroundRenderComponent(std::vector<std::string> string_paths);
    void init() override;
    void update() override;

protected:
    void loadNextImage() override;

private:
    bool currentSpriteFinished();
    void loadErrorBackgroundImage();

    std::vector<std::string> _string_paths;
};
#endif //BACKGROUND_RENDER_COMPONENT_H