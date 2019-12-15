//
// Created by axelmpm on 14/12/19.
//

#include "EnemySound.h"

EnemySound::EnemySound(State *state, Sounds soundsConfig) : Sound(state, soundsConfig) {

}

void EnemySound::handleCurrentState() {
    if (state->current() != previous) {
        previous = state->current();
        switch (state->current()) {
            case PUNCH:
                if (state->isHitting()) {
                    _currentSoundPath = soundsConfig.npcs.hit;
                    state->endHittingFlag();
                }
                break;
            case DYING:
                _currentSoundPath = soundsConfig.npcs.death;
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


