//
// Created by axelmpm on 30/11/19.
//

#include "AnimatedEntity.h"

AnimatedEntity::AnimatedEntity(Will *will, State *state, AnimatedEntityCollitionHandler *collitionHandler,
                               Position *position, Physics *physics, ScreenPosition *screenPosition,
                               StateDrivenAppearance *appearance, Sound *sound, Damage *damage, Life *life,
                               Attack *attack) :

                               PhysicalEntity(state, position, screenPosition, appearance, damage, life, score){

    this->will = will;
    this->collitionHandler = collitionHandler;
    this->physics = physics;
    this->attack = attack;
    this->sound = sound;
}

void AnimatedEntity::update() {

    will->update();
    state->update();
    attack->update();
    physics->update();
    appearance->update();
    sound->update();
}

Sendable *AnimatedEntity::generateSendable() {

    auto renderable = appearance->generateRenderable();
    auto soundable = sound->generateSoundable();

    return new Sendable(renderable, soundable);
}

void AnimatedEntity::drag() {
    physics->drag();
}

bool AnimatedEntity::lifeEmpty() {
    return life->empty();
}

AnimatedEntity::~AnimatedEntity() {

    delete(will);
    delete(collitionHandler);
    delete(physics);
    delete(sound);
    delete(attack);
}