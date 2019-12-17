//
// Created by Tomás Macía on 14/12/2019.
//

#include "AttackingBehavior.h"
#include "PursuitBehavior.h"

AttackingBehavior::AttackingBehavior(IA *owner, EntityManager *manager, Position *subjectPosition) {
    this->owner = owner;
    this->em = manager;
    this->subjectPosition = subjectPosition;
}

void AttackingBehavior::update() {
    if (getDistanceToTarget() >= DISTANCE_TO_START_PURSUIT) {
        this->owner->switchBehavior(TARGET);
        ((PursuitBehavior*) this->owner->getCurrentBehavior())->switchTarget(target); // ASCO
        framesSinceLastPunch = 0;
        return;
    }
    framesSinceLastPunch++;
}

Action AttackingBehavior::getNext() {
    Action action = NONE;

    if (framesSinceLastPunch >= PUNCH_DELAY) {
        framesSinceLastPunch = 0;
        action = PUNCH;
    }

    return action;
}

int AttackingBehavior::getDistanceToTarget() {
    return this->target->getPosition()->getDistanceTo(subjectPosition);
}
