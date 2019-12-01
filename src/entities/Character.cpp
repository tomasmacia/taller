
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
                       appearance, sound, damage,life, score, attack){

    lifes = 3;
    lifeAmount = 100;
    this->life->initializeWith(lifeAmount, lifes);
    this->id = id;
    this->scoreAppearance = scoreAppearance;
}

void Character::notifySuccessfulAttack(int score) {
    this->score->increaseBy(score);
    this->scoreAppearance->update();
}

bool Character::isDisconnected() {
    return state->isDisconnected();
}

void Character::setConnected(int newID) {
    CharacterAppearance* characterAppearance = (CharacterAppearance*) this->appearance;

    state->setConnected();
    characterAppearance->setConnected();
    id->setNew(newID);
}

void Character::setDisconnected() {
    CharacterAppearance* characterAppearance = (CharacterAppearance*) this->appearance;

    state->setDisconnected();
    characterAppearance->setDisconnected();
}

int Character::getID() {
    return id->get();
}

Character::~Character() {
    delete(id);
    delete(scoreAppearance);
}

int Character::setAttackedWith(AttackCode attackCode) {

    int damageInflicted = damage->characterAttackedWith(attack);

    life->decreseBy(damageInflicted);
}
