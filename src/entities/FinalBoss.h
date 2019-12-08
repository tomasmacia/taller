//
// Created by axel on 24/11/19.
//

#ifndef GAME_FINALBOSS_H
#define GAME_FINALBOSS_H


#include "entityHierarchy/AnimatedEntity.h"

class FinalBoss : public AnimatedEntity {

public:
    FinalBoss(CollitionHandler* collitionHandler, Life *life, Damage *damage, Score* score, Position *position,
    State* state, ScreenPosition* screenPosition, StateDrivenAppearance* appearance, Sound* sound,
    Will* will, Physics* physics, Attack* attack, int w, int h, int d);

    int setAttackedWith(AttackCode attack) override ;

    bool isFinalBoss(){return true;}
private:
    int FINAL_BOSS_LIFE_AMOUNT = 500;
};


#endif //GAME_FINALBOSS_H
