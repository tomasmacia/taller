//
// Created by axel on 24/11/19.
//

#ifndef GAME_SCORE_H
#define GAME_SCORE_H


#include "components/appearances/ScoreAppearance.h"
#include "../../enumerates/AttackCode.h"

class Score {

public:
    void increaseBy(int amount);
    int finalBossKilled();
    int barrelAttackedWith(AttackCode attackCode);
    int boxAttackedWith(AttackCode attack);
    int enemyAttackedWith(AttackCode attackCode)
    int enemyKilled();
    int barrelBroken();
    int boxBroken();

    int enemyKilled();

private:
    int BROKEN_BOX_SCORE = 200;
    int BROKEN_BARREL_SCORE = 300;
    int ENEMY_KILLED = 500;
    int FINAL_BOSS_KILLED = 2000;
    int PUNCH_TO_ENEMY = 100;
    int KICK_TO_ENEMY = 400;
    int JUMP_KICK_TO_ENEMY = 400;
    int KNIFE_ATTACK_TO_ENEMY = 400;
    int TUBE_ATTACK_TO_ENEMY = 200;

}

    int current = 0;

};


#endif //GAME_SCORE_H
