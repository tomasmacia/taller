//
// Created by axel on 28/10/19.
//

#include "ToClientPack.h"

//CONSTRUCTORS
//=========================================================================================
ToClientPack::ToClientPack(std::string path, SDL_Rect srcRect, SDL_Rect destRect, bool isFliped){
    this->path = path;
    this->srcRect = srcRect;
    this->destRect = destRect;
    this->fliped = isFliped;
}

ToClientPack::ToClientPack(){
    SDL_Rect aux;
    this->path = "NULL";
    this->srcRect = aux;
    this->destRect = aux;
    this->fliped = false;
}

//API
//=========================================================================================
void ToClientPack::render(std::map<std::string, TextureWrapper*>* loadedTexturesMap){

    TextureWrapper* textureAsociatedToSpritePath;

    //sintaxis estandar para chequear si la key esta en el diccionario
    if (loadedTexturesMap != nullptr) {
        if (loadedTexturesMap->find(path) != loadedTexturesMap->end()){ //si esta en diccionario

            textureAsociatedToSpritePath = loadedTexturesMap->find(path)->second;
        }
        else{//si no fue cargado nunca el sprite

            textureAsociatedToSpritePath = new TextureWrapper();
            textureAsociatedToSpritePath->loadFromFile(path);
            loadedTexturesMap->insert({ path, textureAsociatedToSpritePath });
        }
    }
    textureAsociatedToSpritePath->render(&srcRect,&destRect,fliped);
}


