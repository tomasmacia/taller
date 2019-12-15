
//
// Created by axel on 24/11/19.
//

#include "Character.h"
#include "components/appearances/CharacterAppearance.h"

Character::Character(CollitionHandler* collitionHandler, Life *life, Damage *damage, Score* score, Position *position,
                     State* state, ScreenPosition* screenPosition, StateDrivenAppearance* appearance, Sound* sound,
                     Will* will, Physics* physics, Attack* attack, ID* id, ScoreAppearance* scoreAppearance, int w, int h, int d) :

        AnimatedEntity(collitionHandler, life, damage, score, position, state, screenPosition, appearance, sound,
                       will, physics, attack, w, h, d){

    this->life->initializeWith(CHARACTER_LIFE_AMOUNT, AMOUNT_OF_LIFES_CHARACTER);
    this->id = id;
    this->scoreAppearance = scoreAppearance;
}

list<Sendable *> Character::generateSendable() {
    list<Sendable *> sendables = PhysicalEntity::generateSendable();

    auto scoreAppearanceSendable = new Sendable(scoreAppearance->generateRenderable(), nullptr);
    sendables.push_back(scoreAppearanceSendable);
    return sendables;
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

    if (state->current() != BEING_ATTACKED){

        AnimatedEntity::setAttackedWith(attackCode);
        int damageInflicted = damage->characterAttackedWith(attackCode);

        life->decreseBy(damageInflicted);
    }
}

void Character::resetAt(int x, int y, int z) {
    setPosition(x,y,z);
}

void Character::removeWeapon() {
    if (attack->hasWeapon()){
        attack->dropWeapon();
    }
}
