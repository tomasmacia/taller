//
// Created by Tomás Macía on 15/10/2019.
//

#ifndef GAME_TEXTUREWRAPPER_H
#define GAME_TEXTUREWRAPPER_H

#include <string>
#include <vector>
#include <SDL2/SDL_render.h>


class TextureWrapper {
public:
    // Initializes variables
    TextureWrapper();

    // Deallocates memory
    ~TextureWrapper();

    // Loads image at specified path
    bool loadFromFile(std::string path, std::vector<int> rgb = std::vector<int>{88,184,248}); // light blue default

    // Deallocates texture
    void free();

    // Renders texture at given point
    void render(SDL_Rect* srcRect, SDL_Rect* destRect, bool flip);

    void setWidthAndHeight(int w, int h) {
        mWidth = w;
        mHeight = h;
    }

    // Gets image dimensions
    int getWidth() {
        return mWidth;
    }

    int getHeight() {
        return mHeight;
    }

    static void measureWidthAndHeighthOf(std::string spritePath,int* width, int* hegith); //si habias iniciado SDL antes en este thread, este metodo lo corta

private:
    void getRenderer();
    static SDL_Renderer* staticGetRenderer();

    // The actual hardware texture
    SDL_Texture* mTexture = nullptr;

    // Image dimensions
    int mWidth;
    int mHeight;

    SDL_Renderer* renderer = nullptr;
};

#endif //GAME_TEXTUREWRAPPER_H
