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
    int thisPlayerId = _id->get();

    while (!inputs.empty()){

        currentInput = inputs.front();
        currentInputPlayerId = std::get<1>(currentInput);


        string action;
        switch (std::get<0>(currentInput)){
        case UP:
            action = "UP";
            break;
        case END_UP:
            action = "END_UP";
            break;
        case DOWN:
            action = "DOWN";
            break;
        case END_DOWN:
            action = "END_DOWN";
            break;
        case LEFT:
            action = "LEFT";
            break;
        case END_LEFT:
            action = "END_LEFT";
            break;
        case RIGHT:
            action = "RIGHT";
            break;
        case END_RIGHT:
            action = "END_RIGHT";
            break;
        }

        cout<<"ACTION: "<<action<<endl;


        if (currentInputPlayerId == thisPlayerId) {
            cout<<std::get<1>(currentInput)<<endl;
            playerInputs.push_back(currentInput);
        }
        inputs.pop_front();
    }
}
