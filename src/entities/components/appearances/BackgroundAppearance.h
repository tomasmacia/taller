
#ifndef BACKGROUND_RENDER_COMPONENT_H
#define BACKGROUND_RENDER_COMPONENT_H

#include <vector>
#include <string>
#include "Appearance.h"
#include "../../Screen.h"

using namespace std;

class BackgroundAppearance : public Appearance {

public:
    BackgroundAppearance(Position* position, Screen* screen, string string_path, float parallaxSpeed);

    void update() override ;
    void init();

private:
    Renderable* generateRenderable() override;
    void loadNextImage() override;

    float _parallaxSpeed;
};
#endif //BACKGROUND_RENDER_COMPONENT_H