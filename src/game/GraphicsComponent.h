#ifndef GAME_GRAPHICSCOMPONENT_H
#define GAME_GRAPHICSCOMPONENT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Component.h"
#include "Action.h"


class GraphicsComponent : public Component {

private:
    SDL_Texture *texture;
    SDL_Rect sourceRect;
    SDL_Rect destinationRect;
    

public:
    GraphicsComponent(const char* textureFile);
    ~GraphicsComponent();

    void update() override;
    void render() override;
};

#endif //GAME_GRAPHICSCOMPONENT_H