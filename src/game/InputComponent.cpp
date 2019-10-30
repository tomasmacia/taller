//
// Created by Tomás Macía on 16/10/2019.
//
#include "GameServer.h"
#include "InputComponent.h"
#include "StateComponent.h"
#include "Controller.h"
#include "IDComponent.h"


void InputComponent::update() {
    inputs = GameServer::getInstance().getController()->getInput(); //obtengo una copia de todos los inputs de todos los clientes

    std::tuple<Action,int> currentInput;
    Action currentInputAction;
    int currentInputPlayerId;
    int thisPlayerId = entity->getComponent<IDComponent>()->getId();

    while (!inputs.empty()){

        currentInput = inputs.front();
        currentInputAction = std::get<0>(currentInput);
        currentInputPlayerId = std::get<1>(currentInput);

        if (currentInputPlayerId == thisPlayerId){
            entity->getComponent<StateComponent>()->setIncomingAction(currentInputAction);
        }
        inputs.pop_front();
    }
}
