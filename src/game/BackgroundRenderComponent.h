
#ifndef BACKGROUND_RENDER_COMPONENT_H
#define BACKGROUND_RENDER_COMPONENT_H

#include <vector>
#include <string>
#include "RenderComponent.h"


class BackgroundRenderComponent : public RenderComponent {
public:
    BackgroundRenderComponent(std::string string_path, float parallaxSpeed);
    void init() override;
    void update() override;
    void render() override;

protected:
    void loadNextImage() override;
    void updatePosition() override {} 
    //en los fondos no quiero mover donde se pone el fondo en la window,
    // sino de donde saco la el cacho de fondo a mostrar

private:
    void loadErrorBackgroundImage();
    float _parallaxSpeed;
};
#endif //BACKGROUND_RENDER_COMPONENT_H