//
// Created by Tomás Macía on 21/09/2019.
//
#include "TextureManager.h"
#include "game.h"
#include <SDL_image.h>

SDL_Texture* TextureManager::loadTexture(const char *textureFile) {
    SDL_Texture *texture = nullptr;
    SDL_Surface *surface = IMG_Load(textureFile);
    if (surface) {
        texture = SDL_CreateTextureFromSurface(Game::getInstance().getRenderer(), surface);
        SDL_FreeSurface(surface);
    }
    return texture;
}