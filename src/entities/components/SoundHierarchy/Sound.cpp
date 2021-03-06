//
// Created by axel on 24/11/19.
//

#include <iostream>
#include "Sound.h"

Sound::Sound(State *state, Sounds soundsConfig) {
    this->soundsConfig = soundsConfig;
    this->state = state;
}

string Sound::getCurrent() {
    return _currentSoundPath;
}

void Sound::update() {
    handleCurrentState();
}

Soundable *Sound::generateSoundable() {

    if (_currentSoundPath != "NONE"){
        return new Soundable(_currentSoundPath,false);
    }
    else{
        return nullptr;
    }
}
