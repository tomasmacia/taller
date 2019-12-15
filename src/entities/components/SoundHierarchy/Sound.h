//
// Created by axel on 24/11/19.
//

#ifndef GAME_SOUND_H
#define GAME_SOUND_H

#include <string>
#include <config/Sounds.h>
#include "../State.h"
#include "../../../net/messaging/Soundable.h"

using namespace std;

class Sound {

public:
    Sound(State* state, Sounds soundsConfig);

    void update();

    string getCurrent();
    Soundable* generateSoundable();

protected:
    Sounds soundsConfig;
    State* state = nullptr;

    string _currentSoundPath = "NONE";
    Action previous = NONE;

    virtual void handleCurrentState() = 0;
};


#endif //GAME_SOUND_H
