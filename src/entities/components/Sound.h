//
// Created by axel on 24/11/19.
//

#ifndef GAME_SOUND_H
#define GAME_SOUND_H

#include <string>
#include "State.h"
#include "../../net/messaging/Soundable.h"

using namespace std;

class Sound {

public:
    Sound(State* state);

    void update();

    string getCurrent();
    Soundable* generateSoundable();

private:
    State* state = nullptr;

    string _currentSoundPath;
};


#endif //GAME_SOUND_H
