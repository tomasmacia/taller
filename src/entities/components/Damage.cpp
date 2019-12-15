//
// Created by axel on 24/11/19.
//

#include "Damage.h"

int Damage::enemyAttackedWith(AttackCode attackCode) {

    switch (attackCode){
        case PUNCH_ATTACK:
            return PUNCH_DAMAGE_TO_ENEMY;
        case KICK_ATTACK:
            return KICK_DAMAGE_TO_ENEMY;
        case JUMP_KICK_ATTACK:
            return JUMP_KICK_DAMAGE_TO_ENEMY;
        case KNIFE:
            return KNIFE_DAMAGE_TO_ENEMY;
        case TUBE:
            return TUBE_DAMAGE_TO_ENEMY;
    }
}

int Damage::boxAttackedWith(AttackCode attack) {
    return 1;
}

int Damage::barrelAttackedWith(AttackCode attackCode) {
    return 1;
}

int Damage::characterAttackedWith(AttackCode attackCode) {
    return ENEMY_TO_CHARACTER_DAMAGE;
}


