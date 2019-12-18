#include "PatrolBehavior.h"

PatrolBehavior::PatrolBehavior(IA* owner, EntityManager* manager, Position* subjectPosition){
    this->owner = owner;
    this->manager = manager;
    this->subjectPosition = subjectPosition;
}

Action PatrolBehavior::getNext(){
    return NONE;
//    if (side == 1){
//        return RIGHT;
//    } else {
//        return LEFT;
//    }
}

void PatrolBehavior::update(){
//    if (sideChangeCounter >= SIDE_CHANGE_DELAY){
//        sideChangeCounter = 0;
//         if (side == 1){
//            side ++;
//        } else {
//            side =1;
//        }
//    }
//    sideChangeCounter++;

    if (playerDetectCounter >= PLAYER_DETECTION_DELAY){
        playerDetectCounter = 0;
        Character *target = getNearPlayer();
        if (target != nullptr) {
            //this->owner->changeBehavior(new PursuitBehavior(this->target,this->owner,manager,subjectPosition));
            this->owner->switchBehavior(TARGET);
            ((PursuitBehavior*)this->owner->getCurrentBehavior())->switchTarget(target); // ASCO
        }
    }
    playerDetectCounter++;
}


Character* PatrolBehavior::getNearPlayer() {
    Character *nearCharacter = nullptr;

    for(auto const& player : manager->getPlayers()) {
        if (!player->isDisconnected() && !player->dead() && player->getPosition()->getDistanceTo(this->subjectPosition) < PLAYER_DETECTION_RANGE) {
            nearCharacter = player;
        }
    }

    return nearCharacter;
}