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
//    int xdif = abs(subjectPosition->getX() - target->getX());
//    int ydif = abs(subjectPosition->getY() - target->getY());
//
//    if (xdif >= PUNCH_RANGE) {
//        if (xdif < ydif) {
//            if (ydif > 0) {
//                result = DOWN;
//            } else {
//                result = UP;
//            }
//        } else {
//            if (xdif > 0) {
//                result = RIGHT;
//            } else {
//                result = LEFT;
//            }
//        }
//    }

    return result;
}