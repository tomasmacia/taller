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

void TextureWrapper::render(Rect* src, Rect* dest,bool flip = false) {

    SDL_Rect srcRect = {src->x,src->y,src->w,src->h};
    SDL_Rect destRect = {dest->x,dest->y,dest->w,dest->h};

    if (mTexture == nullptr){

        SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0x00, 0xFF );
        SDL_RenderFillRect( renderer, &destRect );

    }else{
        if (flip)
            SDL_RenderCopyEx( renderer, mTexture, &srcRect, &destRect, 0, NULL, SDL_FLIP_HORIZONTAL);
        else
            SDL_RenderCopy(renderer, mTexture, &srcRect, &destRect );
    }
}

//MANAGING RENDERER
//=========================================================================================
SDL_Renderer* TextureWrapper::staticGetRenderer(){

    SDL_Renderer* _renderer = nullptr;

    if (GameClient::isActive()){                                //hago esto porque si no pregunto y pido directamente me va a crear una instancia de Game getY no quiero
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