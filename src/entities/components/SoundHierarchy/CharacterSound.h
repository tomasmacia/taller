//
// Created by axelmpm on 14/12/19.
//

#ifndef GAME_CHARACTERSOUND_H
#define GAME_CHARACTERSOUND_H


#include "Sound.h"

class CharacterSound : public  Sound{

public:
    CharacterSound(State* state, Sounds soundsConfig);

    void handleCurrentState() override ;

};


#endif //GAME_CHARACTERSOUND_H
