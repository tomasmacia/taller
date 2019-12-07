//
// Created by axel on 28/11/19.
//

#include "PhysicalEntity.h"


PhysicalEntity::PhysicalEntity(CollitionHandler* collitionHandler, Life *life, Damage *damage, Score* score, Position *position,
                               State* state, ScreenPosition* screenPosition, StateDrivenAppearance* appearance, Sound* sound)

                               : Entity(collitionHandler){
    this->life = life;
    this->damage = damage;
    this->score = score;
    this->position = position;
    this->state = state;
    this->screenPosition = screenPosition;
    this->appearance = appearance;
    this->sound = sound;
}

void PhysicalEntity::update() {
    state->update();
    sound->update();
    appearance->update();
}

list<Sendable*> PhysicalEntity::generateSendable() {

    list<Sendable*> sendables;

    sendables.splice(sendables.end(),collitionHandler->generateSendable());
    sendables.splice(sendables.end(),life->generateSendable());

    auto entityRenderable = appearance->generateRenderable();
    auto entitySoundable = sound->generateSoundable();
    auto entitySendable = new Sendable(entityRenderable, entitySoundable);
    sendables.push_back(entitySendable);

    return sendables;
}

int PhysicalEntity::setAttackedWith(AttackCode attackCode) {
    state->setBeingAttacked();
    return 0;
}

int PhysicalEntity::getX() {
    return position->getX();
}

int PhysicalEntity::getY() {
    return position->getY();
}

int PhysicalEntity::getZ() {
    return position->getZ();
    }

void PhysicalEntity::setPosition(int x, int y, int z){
        position->setPosition(x,y,z);
    }


bool PhysicalEntity::lifeEmpty() {
    return life->empty();
}

bool PhysicalEntity::dead() {
    return state->dead();
}

PhysicalEntity::~PhysicalEntity() {

    delete(life);
    delete(damage);
    delete (score);
    delete(position);
    delete(state);
    delete(screenPosition);
    delete(appearance);
}