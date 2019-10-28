//
// Created by Tomás Macía on 15/10/2019.
//

#include <SDL2/SDL_image.h>
#include "TextureWrapper.h"
#include "GameClient.h"

TextureWrapper::TextureWrapper() {
    //Initialize
    mTexture = nullptr;
    mWidth = 0;
    mHeight = 0;
    renderer = GameClient::getInstance().getRenderer();
}

TextureWrapper::~TextureWrapper() {
    //Deallocate
    free();
    //LogManager::logDebug("Memoria de TextureWrapper liberada");
}

bool TextureWrapper::loadFromFile(std::string path, std::vector<int> rgb) {
    // Get rid of preexisting texture
    free();

    // The final texture
    SDL_Texture* newTexture = nullptr;
    SDL_Surface* loadedSurface;

    // Load image at specified path
    loadedSurface = IMG_Load( path.c_str() );
    if (loadedSurface == nullptr) {
        LogManager::logError("No se pudo cargar la imagen " + path + ". SDL_image Error: " + IMG_GetError());

    }else{
        // Color key image
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, rgb.at(0), rgb.at(1), rgb.at(2)));

        // Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        if (newTexture == nullptr) {
            LogManager::logError("No se pudo crear la textura de la imagen " + path + ". SDL Error: " + SDL_GetError());
        }else{
            // Return success
            mTexture = newTexture;

            // Sets texture dimentions
            SDL_QueryTexture(mTexture, nullptr, nullptr, &mWidth, &mHeight);
        }
        // Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    return mTexture != nullptr;
}

void TextureWrapper::free() {
    // Free texture if it exists
    if(mTexture != nullptr) {
        SDL_DestroyTexture( mTexture);
        mTexture = nullptr;
        mWidth = 0;
        mHeight = 0;
    }
}

void TextureWrapper::render(SDL_Rect* srcRect, SDL_Rect* destRect,bool flip = false) {

    if (mTexture == nullptr){

        SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0x00, 0xFF );
        SDL_RenderFillRect( renderer, destRect );

    }else{
        if (flip)
            SDL_RenderCopyEx( renderer, mTexture, srcRect, destRect, 0, NULL, SDL_FLIP_HORIZONTAL);
        else
            SDL_RenderCopy(renderer, mTexture, srcRect, destRect );
    }
}

void TextureWrapper::measureWidtAndHeighthOf(std::string spritePath,int* width, int* hegith){

    //Solo para generar una textura temporal y medir el width del sprite
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    int aux1 = 1000;
    int aux2 = 1000;
    SDL_Window* temporaryWindow = SDL_CreateWindow("Final Fight", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, aux1, aux2, 0);
    SDL_Renderer* temporaryRenderer = SDL_CreateRenderer(temporaryWindow, -1, SDL_RENDERER_PRESENTVSYNC);
    SDL_Surface* temporarySurface = IMG_Load( spritePath.c_str() );
    SDL_Texture* temporaryTexture = SDL_CreateTextureFromSurface( temporaryRenderer, temporarySurface );
    SDL_QueryTexture(temporaryTexture, nullptr, nullptr, width, hegith);

    //Libero memoria y cierro el SDL que abri en este metodo de forma temporal
    SDL_FreeSurface(temporarySurface);
    SDL_DestroyTexture(temporaryTexture);
    SDL_DestroyWindow(temporaryWindow);
    SDL_DestroyRenderer(temporaryRenderer);
    SDL_Quit();
}

