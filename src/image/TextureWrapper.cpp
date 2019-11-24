//
// Created by Tomás Macía on 15/10/2019.
//

#include <SDL2/SDL_image.h>
#include "TextureWrapper.h"
#include "../game/GameClient.h"
#include "../game/GameServer.h"

SDL_Renderer* _renderer = nullptr;

//CONSTRUCTOR
//=========================================================================================
TextureWrapper::TextureWrapper() {
    //Initialize
    mTexture = nullptr;
    mWidth = 0;
    mHeight = 0;
    getRenderer();
}

//API
//=========================================================================================
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

void TextureWrapper::measureWidthAndHeighthOf(std::string spritePath,int* width, int* hegith){

    //Solo para generar una textura temporal y medir el width del sprite
    SDL_Surface* temporarySurface = IMG_Load( spritePath.c_str() );
    SDL_Texture* temporaryTexture = SDL_CreateTextureFromSurface(staticGetRenderer(), temporarySurface );
    SDL_QueryTexture(temporaryTexture, nullptr, nullptr, width, hegith);

    //Libero memoria y cierro el SDL que abri en este metodo de forma temporal
    SDL_FreeSurface(temporarySurface);
    SDL_DestroyTexture(temporaryTexture);
}

//MANAGING RENDERER
//=========================================================================================
SDL_Renderer* TextureWrapper::staticGetRenderer(){

    SDL_Renderer* _renderer = nullptr;

    if (GameClient::isActive()){                                //hago esto porque si no pregunto y pido directamente me va a crear una instancia de Game y no quiero
        _renderer = GameClient::getInstance().getRenderer();
    }
    else if (GameServer::isActive()){
        _renderer = GameServer::getInstance().getRenderer();
    }

    return _renderer;
}

void TextureWrapper::getRenderer(){
    renderer = staticGetRenderer();
}

//DESTROY
//=========================================================================================
TextureWrapper::~TextureWrapper() {
    free();
    //LogManager::logDebug("Memoria de TextureWrapper liberada");
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