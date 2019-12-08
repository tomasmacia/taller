//
// Created by axel on 24/11/19.
//

#ifndef GAME_ENEMY_H
#define GAME_ENEMY_H


#include "entityHierarchy/AnimatedEntity.h"

class Enemy : public AnimatedEntity{

public:
    Enemy(CollitionHandler* collitionHandler, Life *life, Damage *damage, Score* score, Position *position,
          State* state, ScreenPosition* screenPosition, StateDrivenAppearance* appearance, Sound* sound,
          Will* will, Physics* physics, Attack* attack, int w, int h, int d);

    int setAttackedWith(AttackCode attack) override ;

    bool isEnemy(){return true;}
private:
    int ENEMY_LIFE_AMOUNT = 100;
};


#endif //GAME_ENEMY_H
