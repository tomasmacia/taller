//
// Created by axel on 24/11/19.
//

#include "Character.h"
#include "../game/CollitionManager.h"
#include "components/collition/EntityWithAttackCollitionHandler.h"

Character::Character(int x, int y, int z, int w, int h, int id, int walkingSpeed, const CharacterXML& characterConfig,
                    InputPoller* inputPoller, Screen* screen, CollitionManager* collitionManager) {

    _wakingSpeed = walkingSpeed;

    this->id = new ID(id);

    this->will = inputPoller;
    this->state = new State(will);
    this->damage = new CharacterDamage();

    auto punchBox = collitionManager->addNewCollitionBox(x, y, z, w, h, -1, this);
    auto kickBox = collitionManager->addNewCollitionBox(x, y, z, w, h, -1, this);
    auto collitionBox = collitionManager->addNewCollitionBox(x, y, z, w, h, -1, this);
    this->collitionHandler = new EntityWithAttackCollitionHandler(punchBox, kickBox, collitionBox, collitionManager, state);

    this->position = new Position(x, y, z, collitionHandler);
    this->physics = new Physics(state,position,walkingSpeed);
    this->screenPosition = new ScreenPosition(position,screen);
    this->appearance = new CharacterAppearance(w, h, screenPosition, state, characterConfig);
    this->sound = new CharacterSound(state);
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

    auto renderable = appearance->generateRenderable();
    auto soundable = sound->generateSoundable();

    return new Sendable(renderable, soundable);
}

Character::~Character() {

    delete(life);
    delete(score);
    delete(damage);

    delete(id);
    delete(will);
    delete(state);
    delete(collitionHandler);
    delete(position);
    delete(physics);
    delete(screenPosition);
    delete(appearance);
    delete(sound);
}

void Character::drag() {
    physics->drag();
}

bool Character::isDisconnected() {
    return state->isDisconnected();
}

void Character::setConnected(int newID) {
    state->setConnected();
    appearance->setConnected();
    id->setNew(newID);
}

int Character::getID() {
    return id->get();
}

void Character::setDisconnected() {
    state->setDisconnected();
    appearance->setDisconnected();
}

