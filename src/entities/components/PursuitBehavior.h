#ifndef GAME_PURSUITBEHAVIOR_H
#define GAME_PURSUITBEHAVIOR_H

#include "PatrolBehavior.h"

const int PURSUIT_MAX_DURATION = 600;
const int PUNCH_RANGE = 20;

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
    bool nearTarget = false;
    Character* target;
    IA* owner;
    EntityManager* manager;
    Position* subjectPosition;
};


#endif