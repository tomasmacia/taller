#include "PursuitBehavior.h"
#include "EnemyBehaviorType.h"

PursuitBehavior::PursuitBehavior(Character* target, IA* owner, EntityManager* manager, Position* subjectPosition){
    this->owner = owner;
    this->target = target;
    this->manager = manager;
    this->subjectPosition = subjectPosition;
};

void PursuitBehavior::update() {
    pursuitDurationCounter++;
    if (pursuitDurationCounter >= PURSUIT_MAX_DURATION){
        //this->owner->changeBehavior(new PatrolBehavior(owner,manager,subjectPosition));
        this->owner->switchBehavior(PATROL);
        pursuitDurationCounter = 0;
    };
}

Action PursuitBehavior::getNext() {
    Action result = NONE;
    int distance = target->getPosition()->getDistanceTo(subjectPosition);

    if (distance >= PUNCH_RANGE) {
        int xdif = target->getX() - subjectPosition->getX();
        int zdif = target->getZ() - subjectPosition->getZ();
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
    }

    return result;
}