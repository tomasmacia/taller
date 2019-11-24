//
// Created by axel on 12/11/19.
//

#ifndef GAME_NONCHARACTERLEVELLIMITS_H
#define GAME_NONCHARACTERLEVELLIMITS_H

#include "LevelLimits.h"

class NonCharacterLevelLimits : public LevelLimits {

public:
    NonCharacterLevelLimits(int windowWidth, int windowHeight, int levelWidth, CameraComponent* camera);
    void update() override {}

protected:
    void initialize(int windowWidth, int windowHeight, int levelWidth, CameraComponent* camera) override ;

};


#endif //GAME_NONCHARACTERLEVELLIMITS_H
