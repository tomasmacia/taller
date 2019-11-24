//
// Created by axel on 12/11/19.
//

#ifndef GAME_CHARACTERLEVELLIMITS_H
#define GAME_CHARACTERLEVELLIMITS_H

#include "LevelLimits.h"

class CharacterLevelLimits : public LevelLimits {

public:
    CharacterLevelLimits(int windowWidth, int windowHeight, int levelWidth, Screen* camera);
    void update() override ;

protected:
    void initialize(int windowWidth, int windowHeight, int levelWidth, Screen* camera) override ;

};


#endif //GAME_CHARACTERLEVELLIMITS_H
