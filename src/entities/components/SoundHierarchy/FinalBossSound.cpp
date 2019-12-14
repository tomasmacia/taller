//
// Created by axelmpm on 14/12/19.
//

#include "FinalBossSound.h"

FinalBossSound::FinalBossSound(State *state, Sounds soundsConfig) : Sound(state, soundsConfig) {

}

void FinalBossSound::handleCurrentState() {
    switch (state->current()){
        case PUNCH:
            _currentSoundPath = soundsConfig.npcs.hit;
            state->endHittingFlag();
            break;
        case DYING:
            _currentSoundPath = soundsConfig.boss.death;
            break;
        default:
            _currentSoundPath = "NONE";
            break;
    }
}
