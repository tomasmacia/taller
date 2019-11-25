//
// Created by axel on 24/11/19.
//

#ifndef GAME_SOUND_H
#define GAME_SOUND_H

#include <string>
using namespace std;

class Sound {

public:
    string getCurrent();

private:
    string _currentSoundPath;
};


#endif //GAME_SOUND_H
