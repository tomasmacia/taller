//
// Created by Tomás Macía on 15/10/2019.
//

#ifndef GAME_TEXTUREWRAPPER_H
#define GAME_TEXTUREWRAPPER_H

#include <string>
#include <vector>
#include <SDL2/SDL_render.h>
#include "Rect.h"


class TextureWrapper {
public:
    TextureWrapper();
    ~TextureWrapper();

    //API
    //===============================
    bool loadFromFile(std::string path, std::vector<int> rgb = std::vector<int>{88,184,248}); // light blue default
    void render(Rect* srcRect, Rect* destRect, bool flip);
    static void measureWidthAndHeighthOf(std::string spritePath,int* width, int* hegith); //si habias iniciado SDL antes en este thread, este metodo lo corta

    //SETTERS
    //===============================
    void setWidthAndHeight(int w, int h) {
        mWidth = w;
        mHeight = h;
    }

    //GETTERS
    //===============================
    int getWidth() {
        return mWidth;
    }

    int getHeight() {
        return mHeight;
    }

private:
    //MANAGING RENDERER
    //===============================
    void getRenderer();
    static SDL_Renderer* staticGetRenderer();

    //DESTROY
    //===============================
    void free();

    //ATRIBUTES
    //===============================
    // The actual hardware texture
    SDL_Texture* mTexture = nullptr;

    // Image dimensions
    int mWidth;
    int mHeight;

    SDL_Renderer* renderer = nullptr;
};

#endif //GAME_TEXTUREWRAPPER_H
