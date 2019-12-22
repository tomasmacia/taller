//
// Created by axelmpm on 14/12/19.
//

#include "BoxSound.h"

BoxSound::BoxSound(State *state, Sounds soundsConfig) : Sound(state, soundsConfig) {
}

void BoxSound::handleCurrentState() {
    if (state->current() != previous) {
        previous = state->current();
        switch (state->current()) {
            case DYING:
                _currentSoundPath = soundsConfig.utilities.boxBreak;
                break;
            default:
                _currentSoundPath = "NONE";
                break;
        }
    }
    else{
        _currentSoundPath = "NONE";
    }
}
