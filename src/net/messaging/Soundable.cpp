//
// Created by axel on 24/11/19.
//

#include "Soundable.h"

Soundable::Soundable(string soundPath, bool isMusic) {

    this->_soundPath = soundPath;
    this->_isMusic = isMusic;

}

string Soundable::getPath() {
    return _soundPath;
}

bool Soundable::getBoolMusic() {
    return _isMusic;
}

void Soundable::play(std::map<string, SoundWrapper *> *loadedSoundsMap) {

    SoundWrapper* soundAsociatedToSpritePath = nullptr;

    //sintaxis estandar para chequear si la key esta en el diccionario
    if (loadedSoundsMap != nullptr) {
        if (loadedSoundsMap->find(_soundPath) != loadedSoundsMap->end()){ //si esta en diccionario

            soundAsociatedToSpritePath = loadedSoundsMap->find(_soundPath)->second;
        }
        else{//si no fue cargado nunca el sprite

            soundAsociatedToSpritePath = new SoundWrapper(_isMusic);
            soundAsociatedToSpritePath->load(_soundPath);
            loadedSoundsMap->insert({_soundPath, soundAsociatedToSpritePath });
        }
    }

    if (soundAsociatedToSpritePath != nullptr) {
        soundAsociatedToSpritePath->play();
    }

}
