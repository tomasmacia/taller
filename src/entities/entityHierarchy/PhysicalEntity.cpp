//
// Created by axel on 28/11/19.
//

#include "PhysicalEntity.h"


PhysicalEntity::PhysicalEntity(CollitionHandler* collitionHandler, Life *life, Damage *damage, Score* score, Position *position,
                               State* state, ScreenPosition* screenPosition, StateDrivenAppearance* appearance, Sound* sound, int w, int h, int d )

                               : Entity(collitionHandler){
    this->w = w;
    this->h = h;
    this->d = d;

    this->life = life;
    this->damage = damage;
    this->score = score;
    this->position = position;
    this->state = state;
    this->screenPosition = screenPosition;
    this->appearance = appearance;
    this->sound = sound;
}

list<Sendable*> PhysicalEntity::generateSendable() {

    list<Sendable*> sendables;

    sendables.splice(sendables.end(),collitionHandler->generateSendable());

    auto entityRenderable = appearance->generateRenderable();
    auto entitySoundable = sound->generateSoundable();

    if (entityRenderable != nullptr || entitySoundable != nullptr) {
        auto entitySendable = new Sendable(entityRenderable, entitySoundable);
        sendables.push_back(entitySendable);
    }

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
        position->setPosition(x + w/2,y + h/2 ,z + d/2);
    collitionHandler->setAllCollitionBoxCenterAt(x + w / 2, y + h / 2, z + d / 2);
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

void PhysicalEntity::stopBeingAttacked() {

    if (lifeEmpty()){
        state->setDying();                          //TODO PELIGROSISIMO! si la vida no maneja a tiempo el reponerse, si el entity tiene mas de una vida esto rompe todo
        collitionHandler->eraseCollitionBoxes();    //TODO PELIGROSISIMO! si la vida no maneja a tiempo el reponerse, si el entity tiene mas de una vida esto rompe todo
    }
    else{
        state->endBeingAttacked();
    }
}

int PhysicalEntity::getLeftLimitX() {
    return position->getX() - w/2;
}

int PhysicalEntity::getRightLimitX() {
    return position->getX() + w/2;
}

Point *PhysicalEntity::getPos() {
    return position->get();
}
