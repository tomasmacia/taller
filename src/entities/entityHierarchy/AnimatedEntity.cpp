//
// Created by axelmpm on 30/11/19.
//

#include "AnimatedEntity.h"

AnimatedEntity::AnimatedEntity(Will *will, State *state, AnimatedEntityCollitionHandler *collitionHandler,
                               Position *position, Physics *physics, ScreenPosition *screenPosition,
                               StateDrivenAppearance *appearance, Sound *sound, Damage *damage, Life *life) {
    this->will = will;
    this->state = state;
    this->collitionHandler = collitionHandler;
    this->position = position;
    this->physics = physics;
    this->screenPosition = screenPosition;
    this->appearance = appearance;
    this->damage = damage;
    this->life = life;
}

void AnimatedEntity::update() {

    will->update();
    state->update();
    damage->update();
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

AnimatedEntity::~AnimatedEntity() {

    delete(life);
    delete(damage);
    delete(will);
    delete(state);
    delete(collitionHandler);
    delete(position);
    delete(physics);
    delete(screenPosition);
    delete(appearance);
    delete(sound);
}