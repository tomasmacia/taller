//
// Created by axel on 24/11/19.
//

#include "Sound.h"

string Sound::getCurrent() {
    return _currentSoundPath;
}

Sound::Sound(State *state) {
    this->state = state;
}
