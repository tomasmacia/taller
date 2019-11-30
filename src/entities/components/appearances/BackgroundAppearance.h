
#ifndef BACKGROUND_RENDER_COMPONENT_H
#define BACKGROUND_RENDER_COMPONENT_H

#include <vector>
#include <string>
#include "Appearance.h"

using namespace std;

class BackgroundAppearance : public Appearance {

public:
    BackgroundAppearance(Screen* screen, string string_path, float parallaxSpeed);

    void update() override ;
    void init();

protected:
    Renderable* actuallyGenerateRenderable() override;
    void loadNextImage() override;

    Screen* _screen = nullptr;
    float _parallaxSpeed;
};
#endif //BACKGROUND_RENDER_COMPONENT_H