//
// Created by axel on 24/11/19.
//

#ifndef GAME_SOUND_H
#define GAME_SOUND_H

#include <string>
#include "State.h"

using namespace std;

class Sound {

public:
    Sound(State* state);

    string getCurrent();

private:
    State* state = nullptr;

    string _currentSoundPath;
};


#endif //GAME_SOUND_H
