//
// Created by axel on 24/11/19.
//

#ifndef GAME_ENEMY_H
#define GAME_ENEMY_H


#include "entityHierarchy/PositionalEntity.h"

class Enemy : public PositionalEntity{

    int setAttackedWith(AttackCode attack) override ;

};


#endif //GAME_ENEMY_H
