#include "PursuitBehavior.h"
#include "AttackingBehavior.h"
#include "EnemyBehaviorType.h"

PursuitBehavior::PursuitBehavior(Character* target, IA* owner, EntityManager* manager, Position* subjectPosition){
    this->owner = owner;
    this->target = target;
    this->manager = manager;
    this->subjectPosition = subjectPosition;
};

void PursuitBehavior::update() {

    if (nearTarget) {
        this->owner->switchBehavior(ATTACKING);
        ((AttackingBehavior*) this->owner->getCurrentBehavior())->switchTarget(target); // ASCO
        return;
    }

    pursuitDurationCounter++;
    if (pursuitDurationCounter >= PURSUIT_MAX_DURATION) {
//        if (getDistanceToTarget() <= PUNCH_RANGE) {
//            this->owner->switchBehavior(ATTACKING);
//            ((AttackingBehavior*) this->owner->getCurrentBehavior())->switchTarget(target); // ASCO
//        }

        this->owner->switchBehavior(PATROL);

        pursuitDurationCounter = 0;
    }
}

Action PursuitBehavior::getNext() {
    Action result = NONE;
    int xdif = target->getX() - subjectPosition->getX();
    int zdif = target->getZ() - subjectPosition->getZ();

    int offset = 0;

    if (xdif > 0) {
        xdif -= 120;
        offset = -120;
    } else {
        xdif += 120;
        offset = 120;
    }

    Position position(target->getX() + offset, target->getY(), target->getZ(), nullptr);
    int distance = position.getDistanceTo(subjectPosition);

    if (distance >= PUNCH_RANGE) {
        nearTarget = false;
        if (abs(xdif) < abs(zdif)) {
            if (zdif > 0) {
                result = UP;
            } else if (zdif < 0) {
                result = DOWN;
            }
        } else {
            if (xdif > 0) {
                result = RIGHT;
            } else if (xdif < 0) {
                result = LEFT;
            }
        }
    } else {
        nearTarget = true;
    }

    if (result == NONE) {
        result = END_MOVEMENT;
    }

    return result;
}

int PursuitBehavior::getDistanceToTarget() {
    return this->target->getPosition()->getDistanceTo(subjectPosition);
}
