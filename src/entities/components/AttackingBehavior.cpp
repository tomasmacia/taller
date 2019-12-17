//
// Created by Tomás Macía on 14/12/2019.
//

#include "AttackingBehavior.h"

AttackingBehavior::AttackingBehavior(IA *owner, EntityManager *manager, Position *subjectPosition) {
    this->owner = owner;
    this->em = manager;
    this->subjectPosition = subjectPosition;
}

void AttackingBehavior::update() {
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
