//
// Created by axelmpm on 14/12/19.
//

#ifndef GAME_NULLSOUND_H
#define GAME_NULLSOUND_H


#include "Sound.h"

class NullSound : public Sound{

public:
    NullSound(State* state, Sounds soundsConfig);

    void handleCurrentState() override {}
};


#endif //GAME_NULLSOUND_H
