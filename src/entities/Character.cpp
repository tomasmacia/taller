//
// Created by axel on 24/11/19.
//

#include "Character.h"

Character::Character(CharacterSendableGenerator* sendableGenerator, InputPoller* inputPoller) {

    this->will = inputPoller;
    this->state = new State(will);
    this->damage = new CharacterDamage();
    this->ColitionHandler = new CharacterColitionHandler();
    this->position = new Position(colitionManager);
    this->physics = new Physics(state,position);
    this->appearance = new CharacterAppearence(state);
    this->sound = new CharacterSound(state);

    this->sendableGenerator = sendableGenerator;
    this->sendableGenerator->setPosition(position);
    this->sendableGenerator->setSound(sound);
}

void Character::update() {

    will->update();
    state->update();

    damage->update();
    physics->update();
    appearance->update();
    sound->update();
}

Sendable *Character::generateSendable() {
    return sendableGenerator->generateSendable();
}

Character::~Character() {

    delete(life);
    delete(score);
    delete(damage);

    delete(id);
    delete(will);
    delete(state);
    delete(colitionHandler);
    delete(position);
    delete(physics);
    delete(appearance);
    delete(sound);

    delete(sendableGenerator);
}
