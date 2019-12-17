
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
    auto lifebar=new Sendable(life->getAppearance()->actuallyGenerateRenderable(),nullptr);
    sendables.push_back(lifebar);
    auto lifergrey =new Sendable(life->getAppearance()->GenerateRenderableToDisconnect(isDisconnected()),nullptr);
    sendables.push_back(lifergrey);
    return scoreAppearance->numerRenderabls(score->getCurrent(),sendables);    


}

void Character::notifySuccessfulAttack(int score) {
    this->score->increaseBy(score);
    this->scoreAppearance->update();
    //life->getAppearance()->hit();
    //life->decreseBy(20);
    //std::cerr<<life->current<<" - "<<life->amountOfLifes<< std::endl;
}

bool Character::isDisconnected() {
    return state->isDisconnected();
}

void Character::setConnected(int newID) {
    CharacterAppearance* characterAppearance = (CharacterAppearance*) this->appearance;
    auto* animatedEntityCollitionHandler = (AnimatedEntityCollitionHandler*) this->collitionHandler;

    state->setConnected();
    characterAppearance->setConnected();
    animatedEntityCollitionHandler->setConnected();
    id->setNew(newID);
}

void Character::setDisconnected() {
    auto* characterAppearance = (CharacterAppearance*) this->appearance;
    auto* animatedEntityCollitionHandler = (AnimatedEntityCollitionHandler*) this->collitionHandler;

    state->setDisconnected();
    characterAppearance->setDisconnected();
    animatedEntityCollitionHandler->setDisconected();
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
        life->getAppearance()->hit(damageInflicted);
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

int Character::getScore(){
    return score->getCurrent();
}

void Character::setPositionYToScore(int a){
    scoreAppearance->setPositionYSCore(a);
}

void Character::setPositionXToScore(int a){
    scoreAppearance->setPositionXSCore(a);
}

void Character::setPositionYToLife(int a){
    life->setYPositionToLifeBar(a);
}

void Character::setPositionXToLife(int a){
    life->setXPositionToLifeBar(a);
}

void Character::setColorLifeBar(int a){
    life->getAppearance()->pickColor(a);
}