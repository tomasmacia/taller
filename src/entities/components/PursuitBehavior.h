#ifndef GAME_PURSUITBEHAVIOR_H
#define GAME_PURSUITBEHAVIOR_H

#include "PatrolBehavior.h"

const int PURSUIT_MAX_DURATION = 100;
const float PUNCH_RANGE = 20;

class PursuitBehavior : public Will{
    public:
        PursuitBehavior(Character* target, IA* owner,EntityManager* manager,Position* subjectPosition);
        void update() override;
        Action getNext() override;

    private:

        int pursuitDurationCounter = 0;
        Character* target;
        IA* owner;
        EntityManager* manager;
        Position* subjectPosition;
};


#endif