//
// Created by axelmpm on 14/12/19.
//

#ifndef GAME_BOXSOUND_H
#define GAME_BOXSOUND_H


#include "Sound.h"

class BoxSound : public Sound {

public:
    BoxSound(State* state, Sounds soundsConfig);

    void handleCurrentState() override ;

};


#endif //GAME_BOXSOUND_H
