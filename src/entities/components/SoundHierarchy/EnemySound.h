//
// Created by axelmpm on 14/12/19.
//

#ifndef GAME_ENEMYSOUND_H
#define GAME_ENEMYSOUND_H


#include "Sound.h"

class EnemySound : public  Sound{

public:
    EnemySound(State* state, Sounds soundsConfig);

    void handleCurrentState() override ;
};


#endif //GAME_ENEMYSOUND_H
