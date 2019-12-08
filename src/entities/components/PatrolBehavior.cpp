#include "PatrolBehavior.h"

PatrolBehavior::PatrolBehavior(IA* owner, EntityManager* manager, Position* subjectPosition){
    this->owner = owner;
    this->manager = manager;
    this->subjectPosition = subjectPosition;
}

Action PatrolBehavior::getNext(){
    if (side == 1){
        return RIGHT;
    } else {
        return LEFT;
    }
}

void PatrolBehavior::update(){
    if (sideChangeCounter >= SIDE_CHANGE_DELAY){
        sideChangeCounter = 0;
         if (side == 1){
            side ++;
        } else {
            side =1;
        }
    }
    sideChangeCounter++;

    if (playerDetectCounter >= PLAYER_DETECTION_DELAY){
        playerDetectCounter = 0;
        checkForNearbyPlayer();
        if (this->playerDetected){
            this->owner->changeBehavior(new PursuitBehavior(this->target,this->owner,manager,subjectPosition));
        }
    }
}

void PatrolBehavior::checkForNearbyPlayer(){
    for(auto const& i : manager->getPlayers()){
        if (abs(i->getX() - subjectPosition->getX()) < PLAYER_DETECTION_RANGE){
            playerDetected = true;
            target = i;
        }
    }
}