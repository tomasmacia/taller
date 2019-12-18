//
// Created by Tomás Macía on 16/10/2019.
//
#include "../../game/GameServer.h"
#include "InputPoller.h"
#include "../../game/Controller.h"
#include "ID.h"

InputPoller::InputPoller(Controller *controller, ID *id) {
    _controller = controller;
    _id = id;
}

void InputPoller::update() {
    std::list<std::tuple<Action,int>> inputs = _controller->getACopyOfNewInputs(); //obtengo una copia de todos los inputs de todos los clientes
    selectAndStoreInputsFromIncoming(inputs);
}

Action InputPoller::getNext() {

    Action next;

    if (!playerInputs.empty()){

        next = std::get<0>(playerInputs.front());
        playerInputs.pop_front();
    }
    else{
        next = NONE;
    }
    return next;
}

void InputPoller::selectAndStoreInputsFromIncoming(std::list<std::tuple<Action,int>>& inputs){

    std::tuple<Action,int> currentInput;
    int currentInputPlayerId;
    Action currentInputAction;
    int thisPlayerId = _id->get();

    while (!inputs.empty()){

        currentInput = inputs.front();
        currentInputAction = std::get<0>(currentInput);
        currentInputPlayerId = std::get<1>(currentInput);

        if (currentInputPlayerId == thisPlayerId) {
            playerInputs.push_back(currentInput);
        }
        inputs.pop_front();
    }
}
