//
// Created by axelmpm on 14/12/19.
//

#include "CharacterSound.h"

CharacterSound::CharacterSound(State *state, Sounds soundsConfig) : Sound(state, soundsConfig) {

}

void CharacterSound::handleCurrentState() {
    switch (state->current()){
        case PUNCH:
            switch (state->getWeapon()){
                case NO_WEAPON:
                    _currentSoundPath = soundsConfig.players.hit;
                    break;
                case KNIFE:
                    _currentSoundPath = soundsConfig.players.knifeHit;
                    break;
                case TUBE:
                    _currentSoundPath = soundsConfig.players.pipeHit;
                    break;
            }
            state->endHittingFlag();
            break;
        case CROUCH:
            _currentSoundPath = soundsConfig.players.great;
            state->endPickingFlag();
            break;
        case DYING:
            _currentSoundPath = soundsConfig.players.death;
            break;
    }
}
