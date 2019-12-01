//
// Created by axel on 28/11/19.
//

#include "PhysicalEntity.h"


PhysicalEntity::PhysicalEntity(State* state, ScreenPosition* screenPosition, StateDrivenAppearance* appearance,
                            Position *position, Damage *damage, Life *life, Score* score) {

    this->damage = damage;
    this->life = life;
    this->score = score;
    this->state = state;
    this->screenPosition = screenPosition;
    this->appearance = appearance;
    this->position = position;
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

PhysicalEntity::~PhysicalEntity() {

    delete(life);
    delete(damage);
    delete (score);
    delete(state);
    delete(screenPosition);
    delete(appearance);
    delete(position);
}
