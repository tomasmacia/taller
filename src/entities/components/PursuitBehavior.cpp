#include "PursuitBehavior.h"

PursuitBehavior::PursuitBehavior(Character* target,IA* owner,EntityManager* manager,Position* subjectPosition){
    this->owner = owner;
    this->target = target;
    this->manager = manager;
    this->subjectPosition = subjectPosition;
};

void PursuitBehavior::update(){
    pursuitDurationCounter++;
    if (pursuitDurationCounter >= PURSUIT_MAX_DURATION){
        this->owner->changeBehavior(new PatrolBehavior(owner,manager,subjectPosition));
    };
}

Action PursuitBehavior::getNext(){
    Action result = PUNCH;
    float xdif = subjectPosition->getX() - target->getX();
    float ydif = subjectPosition->getY() - target->getY();

    if (xdif >= PUNCH_RANGE){
        if(abs(xdif) < abs(ydif)){
            if(ydif > 0){
                result = DOWN;
            } else {
                result = UP;
            }
        } else {
            if(xdif > 0){
                result = RIGHT;
            } else {
                result = LEFT;
            }
        }
    }
}