//
// Created by axelmpm on 14/12/19.
//

#include <iostream>
#include "CharacterSound.h"

CharacterSound::CharacterSound(State *state, Sounds soundsConfig) : Sound(state, soundsConfig) {

}

void CharacterSound::handleCurrentState() {
    if (state->current() != previous){
        previous = state->current();
        switch (state->current()){
            case END_JUMP:
                _currentSoundPath = soundsConfig.players.jump;
                break;
            case KICK:
                if (state->isHitting()){
                    _currentSoundPath = soundsConfig.players.hit;
                    state->endHittingFlag();
                }
                break;
            case JUMP_KICK:
                if (state->isHitting()){
                    _currentSoundPath = soundsConfig.players.hit;
                    state->endHittingFlag();
                }
                break;
            case PUNCH:
                if (state->isHitting()){
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
                }
                break;
            case CROUCH:
                if (state->justPickedWeapon()){
                    _currentSoundPath = soundsConfig.players.great;
                    state->endPickingFlag();
                }
                break;
            case DYING:
                _currentSoundPath = soundsConfig.players.death;
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
