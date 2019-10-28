//
// Created by Tomás Macía on 16/10/2019.
//
#include "GameServer.h"
#include "InputComponent.h"
#include "StateComponent.h"


void InputComponent::update() {
    actions = GameServer::getInstance().getController()->getInput();
    
    if (!actions.empty()){
        entity->getComponent<StateComponent>()->setIncomingAction(actions.front());
        actions.pop_front();
    }
}
