//
// Created by axelmpm on 30/11/19.
//

#include "AnimatedEntity.h"

AnimatedEntity::AnimatedEntity(CollitionHandler* collitionHandler, Life *life, Damage *damage, Score* score, Position *position,
                               State* state, ScreenPosition* screenPosition, StateDrivenAppearance* appearance, Sound* sound,
                               Will* will, Physics* physics, Attack* attack, int w, int h, int d) :

                               PhysicalEntity(collitionHandler, life, damage, score, position, state, screenPosition, appearance, sound,w,h,d){

    this->will = will;
    this->physics = physics;
    this->attack = attack;
    this->attack->setOwner(this);
}

void AnimatedEntity::update() {

    will->update();
    PhysicalEntity::update();
    physics->update();
    attack->update();
}

void AnimatedEntity::drag() {
    physics->drag();
}

AnimatedEntity::~AnimatedEntity() {

    delete(will);
    delete(physics);
    delete(attack);
}