//
// Created by axelmpm on 14/12/19.
//

#ifndef GAME_FINALBOSSSOUND_H
#define GAME_FINALBOSSSOUND_H


#include "Sound.h"

class FinalBossSound : public Sound{

public:
    FinalBossSound(State* state, Sounds soundsConfig);

    void handleCurrentState() override ;
};


#endif //GAME_FINALBOSSSOUND_H
