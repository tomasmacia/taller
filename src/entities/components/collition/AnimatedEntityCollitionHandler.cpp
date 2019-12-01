//
// Created by axel on 25/11/19.
//
#include <list>
#include "AnimatedEntityCollitionHandler.h"

AnimatedEntityCollitionHandler::AnimatedEntityCollitionHandler(CollitionBox* punchBox, CollitionBox* kickBox, CollitionBox* collitionBox,
                                                               CollitionManager* collitionManager, State* state) {

    _state = state;

    _collitionManager = collitionManager;
    _collitionBoxes = new list<CollitionBox*>();

    _blockingCollitionBox = collitionBox;
    _punchBox = punchBox;
    _kickBox = kickBox;

    _collitionBoxes->push_back(_blockingCollitionBox);
    _collitionBoxes->push_back(_punchBox);
    _collitionBoxes->push_back(_kickBox);
}

AnimatedEntityCollitionHandler::~AnimatedEntityCollitionHandler(){
    _collitionBoxes->clear();
    delete(_collitionBoxes);
}

void AnimatedEntityCollitionHandler::update() {
    handleCurrentState();
}

void AnimatedEntityCollitionHandler::handleCurrentState(){

    switch (_state->current()) {
        case PUNCH:
            addressAttack(_punchBox);
            break;
        case KICK:
            addressAttack(_kickBox);
            break;
        case JUMP_KICK:
            addressAttack(_kickBox);
            break;
        case PICK:
            addressPickIntent();
            break;
    }
}

void AnimatedEntityCollitionHandler::addressAttack(CollitionBox* attackingBoxInUse){

    auto hittedCollitionBox = _collitionManager->getListOfHittedCollitionBox();
    int damage = attackingBoxInUse->owner->getDamage();
    int score = 0;

    for (auto collitionBox : *hittedCollitionBox){
        score += collitionBox->owner->attackWith(damage);
    }
    attackingBoxInUse->owner->increseScoreBy(score);
}

void AnimatedEntityCollitionHandler::addressPickIntent(){

    auto collitionBox = _collitionManager->getFirstPickedCollitionBox();
    collitionBox->owner->setPickedBy(_collitionBox->owner);
}
