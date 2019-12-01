//
// Created by axel on 24/11/19.
//

#ifndef GAME_ENEMY_H
#define GAME_ENEMY_H


#include "entityHierarchy/AnimatedEntity.h"

class Enemy : public AnimatedEntity{

public:
    Enemy(Will* will, State* state, AnimatedEntityCollitionHandler* collitionHandler,
                    Position* position, Physics* physics, ScreenPosition* screenPosition,
                    StateDrivenAppearance* appearance, Sound* sound, Damage* damage,
                    Life* life, ID* id, Score* score, ScoreAppearance* scoreAppearance);

    int setAttackedWith(AttackCode attack) override ;
};


#endif //GAME_ENEMY_H
