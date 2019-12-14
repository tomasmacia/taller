//
// Created by axelmpm on 14/12/19.
//

#include "BarrelSound.h"

BarrelSound::BarrelSound(State *state, Sounds soundsConfig) : Sound(state, soundsConfig) {

}

void BarrelSound::handleCurrentState() {
    if (state->current() != previous) {
        previous = state->current();
        switch (state->current()) {
            case DYING:
                _currentSoundPath = soundsConfig.utilities.barrelBreak;
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
