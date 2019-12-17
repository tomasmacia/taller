//
// Created by Tomás Macía on 14/12/2019.
//

#ifndef GAME_ATTACKINGBEHAVIOR_H
#define GAME_ATTACKINGBEHAVIOR_H

#include "Will.h"
#include "IA.h"
#include "../../game/EntityManager.h"
#include "Position.h"
#include "../Character.h"

class AttackingBehavior : public Will {
public:
    AttackingBehavior(IA* owner, EntityManager* manager, Position* subjectPosition);
    void update() override;
    Action getNext() override;
    ~AttackingBehavior() override {

    }

    void switchTarget(Character *target) {
        this->target = target;
    }

private:
    const int PUNCH_DELAY = 40;
    const int DISTANCE_TO_START_PURSUIT = 130;
    int framesSinceLastPunch = 0;
    IA *owner;
    EntityManager *em;
    Position *subjectPosition;
    Character *target = nullptr;

    int getDistanceToTarget();
};


#endif //GAME_ATTACKINGBEHAVIOR_H
