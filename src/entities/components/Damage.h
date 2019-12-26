//
// Created by axel on 24/11/19.
//

#ifndef GAME_DAMAGE_H
#define GAME_DAMAGE_H


#include "State.h"
#include "../../enumerates/AttackCode.h"

class Damage {

public:
    int characterAttackedWith(AttackCode attackCode);
    int enemyAttackedWith(AttackCode attackCode);
    int boxAttackedWith(AttackCode attack);
    int barrelAttackedWith(AttackCode attackCode);

private:
    int ENEMY_TO_CHARACTER_DAMAGE = 20;
    int PUNCH_DAMAGE_TO_ENEMY = 20;
    int KICK_DAMAGE_TO_ENEMY = 75;
    int JUMP_KICK_DAMAGE_TO_ENEMY = 75;
    int KNIFE_DAMAGE_TO_ENEMY = 50;
    int TUBE_DAMAGE_TO_ENEMY = 35;

};


#endif //GAME_DAMAGE_H
