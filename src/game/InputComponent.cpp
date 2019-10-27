//
// Created by Tomás Macía on 16/10/2019.
//

#include "InputComponent.h"
#include "Game.h"


void InputComponent::update() {
    actions.clear();
    actions = Game::getInstance().getController()->getInput();
}
