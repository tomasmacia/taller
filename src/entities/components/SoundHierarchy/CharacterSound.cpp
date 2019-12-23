//
// Created by axelmpm on 14/12/19.
//

#include "CharacterSound.h"

CharacterSound::CharacterSound(State *state, Sounds soundsConfig) : Sound(state, soundsConfig) {

}

void CharacterSound::handleCurrentState() {

    if (state->current() != previous || weaponWasBeingDroped) {
        if (weaponWasBeingDroped){
            weaponWasBeingDroped = false;
        }
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
                    auto currentWeapon = state->getWeapon();
                    auto prevWeapon = state->getPrevWeapon();
                    bool isDroping = state->dropingWeapon();

                    if (currentWeapon == NO_WEAPON && !isDroping){
                        _currentSoundPath = soundsConfig.players.hit;
                    }
                    else if(currentWeapon == KNIFE || (isDroping && prevWeapon == KNIFE)){
                        _currentSoundPath = soundsConfig.players.knifeHit;
                    }
                    else if(currentWeapon == TUBE || (isDroping && prevWeapon == TUBE)){
                        _currentSoundPath = soundsConfig.players.pipeHit;
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
