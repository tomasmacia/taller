
//
// Created by axel on 24/11/19.
//

#include "Character.h"
#include "components/appearances/CharacterAppearance.h"

Character::Character(Will* will, State* state, AnimatedEntityCollitionHandler* collitionHandler,
                     Position* position, Physics* physics, ScreenPosition* screenPosition,
                     StateDrivenAppearance* appearance, Sound* sound, Damage* damage,
                     Life* life, ID* id, Score* score, ScoreAppearance* scoreAppearance) :

        AnimatedEntity(will, state, collitionHandler, position, physics, screenPosition,
                       appearance, sound, damage,life){
    this->id = id;
    this->score = score;
    this->scoreAppearance = scoreAppearance;
}

bool Character::isDisconnected() {
    return state->isDisconnected();
}

void Character::setConnected(int newID) {
    state->setConnected();
    appearance->setConnected();
    id->setNew(newID);
}

void Character::setDisconnected() {
    state->setDisconnected();
    appearance->setDisconnected();
}

int Character::getID() {
    return id->get();
}

Character::~Character() {

    delete(score);
    delete(id);
}