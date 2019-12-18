#ifndef GAME_PURSUITBEHAVIOR_H
#define GAME_PURSUITBEHAVIOR_H

#include "PatrolBehavior.h"


class PursuitBehavior : public Will {
public:
    PursuitBehavior(Character* target, IA* owner,EntityManager* manager,Position* subjectPosition);
    void update() override;
    Action getNext() override;
    ~PursuitBehavior() override {

    }

    void switchTarget(Character* newTarget) {
        this->target = newTarget;
    }

private:
    int getDistanceToTarget();

    int pursuitDurationCounter = 0;

    const int ENEMY_PUNCH_RANGE = 20;
    const int PURSUIT_MAX_DURATION = 600;
    const int BOSS_PUNCH_RANGE = 30;
    int PUNCH_RANGE = ENEMY_PUNCH_RANGE;
    bool nearTarget = false;
    Character* target;
    IA* owner;
    EntityManager* manager;
    Position* subjectPosition;
};


#endif