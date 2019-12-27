//
// Created by axelmpm on 1/12/19.
//

#ifndef GAME_FINALBOSSAPPEARANCE_H
#define GAME_FINALBOSSAPPEARANCE_H

#include "AnimatedAppearance.h"
#include "../../../XMLparser/config/npc.h"

class FinalBossAppearance : public AnimatedAppearance{
public:
    FinalBossAppearance(int w, int h, ScreenPosition* screenPosition, State* state, NPC npcConfig);

    ~FinalBossAppearance() override = default;

protected:
    void init() override ;
};


#endif //GAME_FINALBOSSAPPEARANCE_H
