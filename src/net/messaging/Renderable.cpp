//
// Created by axel on 28/10/19.
//

#include "Renderable.h"
#include "../../logger/LogManager.h"

//CONSTRUCTORS
//=========================================================================================
Renderable::Renderable(std::string path, Rect srcRect, Rect destRect, bool isFliped){
    this->path = path;
    this->srcRect = srcRect;
    this->destRect = destRect;
    this->fliped = isFliped;
}

//API
//=========================================================================================
void Renderable::render(std::map<std::string, TextureWrapper*>* loadedTexturesMap){

    TextureWrapper* textureAsociatedToSpritePath = nullptr;

    if (!path.empty()){
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

        if (textureAsociatedToSpritePath != nullptr) {
            textureAsociatedToSpritePath->render(&srcRect,&destRect,fliped);
        }
    }
    else{
        LogManager::logError("[GAME]: Se recibio un renderable con un path vacio");
    }
}


