#ifndef GAME_GRAPHICSCOMPONENT_H
#define GAME_GRAPHICSCOMPONENT_H

class GraphicsComponent {

private:

    SDL_Texture *texture;
    SDL_Rect sourceRect;
    SDL_Rect destinationRect;

public:
    GraphicsComponent(const char* textureFile);
    ~GraphicsComponent();

    void setVelocity(int velocity);
};

#endif //GAME_GRAPHICSCOMPONENT_H