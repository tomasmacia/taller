//
// Created by Tomás Macía on 16/10/2019.
//
#include "Game.h"
#include "InputComponent.h"
#include "PhysicsComponent.h"
#include "CharacterRenderComponent.h"
#include <iostream>


void InputComponent::update() {
    actions = Game::getInstance().getController()->getInput();
    
    if (!actions.empty()){
        if (actions.front() == QUIT)
            Game::getInstance().end();
        else{
            entity->getComponent<PhysicsComponent>()->setIncomingAction(actions.front());
            entity->getComponent<CharacterRenderComponent>()->setIncomingAction(actions.front());
            std::cout << "input: "<< actions.front() <<"\n";
            actions.pop_front();
        }
    }
}
