//
// Created by axel on 9/12/19.
//

#include <iostream>
#include "SoundWrapper.h"
#include "../logger/LogManager.h"

SoundWrapper::SoundWrapper(bool isMusic) {

    this->isMusic = isMusic;

}

void SoundWrapper::load(const std::string& path){

    this->path = path;

    if (isMusic){
        music = Mix_LoadMUS(path.c_str());

        if (music == nullptr){

            LogManager::logError("No se pudo cargar la musica " + path );

        }
    }

    else{
        sound = Mix_LoadWAV(path.c_str());

        if (sound == nullptr){

            LogManager::logError("No se pudo cargar el sonido " + path );
        }

    }
}

void SoundWrapper::play() {

    if (isMusic){

        if (Mix_PlayMusic(music, -1) == -1){

            LogManager::logError("No se pudo reproducir la musica");
        }
        else{
            LogManager::logInfo("[GAME]: reproduciendo: " + path);
        }

    }

    else{
        Mix_PlayChannel (-1, sound,0);

        /*
        if ( Mix_PlayChannel (-1, sound,0) == -1){

            LogManager::logError("No se pudo reproducir el sonido ");
        }*/

    }


}

SoundWrapper::~SoundWrapper() {

    Mix_FreeChunk(sound);
    Mix_FreeMusic(music);

}

bool SoundWrapper::playing() {

    if (Mix_PlayingMusic() == 0) {

        return false;
    }

    else{

        return true;
    }
}

void SoundWrapper::play(int cant) {
    if (isMusic){

        if (Mix_PlayMusic(music, cant) == -1){

            LogManager::logError("No se pudo reproducir la musica");
        }
        else{
            LogManager::logInfo("[GAME]: reproduciendo: " + path);
        }

    }

    else{
        Mix_PlayChannel (-1, sound,0);

        /*
        if ( Mix_PlayChannel (-1, sound,0) == -1){

            LogManager::logError("No se pudo reproducir el sonido ");
        }*/

    }
}
