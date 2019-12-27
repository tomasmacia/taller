//
// Created by axelmpm on 14/12/19.
//

#ifndef GAME_BARRELSOUND_H
#define GAME_BARRELSOUND_H


#include "Sound.h"

class BarrelSound : public  Sound{

public:
    BarrelSound(State* state, Sounds soundsConfig);

    void handleCurrentState() override ;
};


#endif //GAME_BARRELSOUND_H
