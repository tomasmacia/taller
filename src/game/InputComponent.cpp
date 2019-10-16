//
// Created by Tomás Macía on 16/10/2019.
//
#include "Game.h"
#include "InputComponent.h"
#include "PhysicsComponent.h"


void InputComponent::update() {
    actions.clear();
    actions = Game::getInstance().getController()->getInput();
 
    if (!actions.empty()){
        if (actions.front() == QUIT)
            Game::getInstance().end();
        else
            entity->getComponent<PhysicsComponent>()->setActions(actions);        
    }
}
