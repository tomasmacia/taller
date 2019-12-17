//
// Created by axel on 24/11/19.
//

#include <iostream>
#include "Score.h"

void Score::increaseBy(int amount) {
    current += amount;
    cout<<"score: "<<current<<endl;
}

int Score::boxAttackedWith(AttackCode attack) {
    return 0;
}

int Score::barrelAttackedWith(AttackCode attackCode) {
    return 0;
}

int Score::boxBroken() {
    return BROKEN_BOX_SCORE;
}

int Score::barrelBroken() {
    return BROKEN_BARREL_SCORE;
}

int Score::finalBossKilled() {
    return FINAL_BOSS_KILLED;
}

int Score::enemyKilled() {
    return ENEMY_KILLED;
}

int Score::enemyAttackedWith(AttackCode attackCode) {

    switch (attackCode){
        case PUNCH_ATTACK:
            return PUNCH_TO_ENEMY;
        case KICK_ATTACK:
            return KICK_TO_ENEMY;
        case JUMP_KICK_ATTACK:
            return JUMP_KICK_TO_ENEMY;
        case KNIFE:
            return KNIFE_ATTACK_TO_ENEMY;
        case TUBE:
            return TUBE_ATTACK_TO_ENEMY;
    }
}

int Score::getCurrent(){
    return current;
}
