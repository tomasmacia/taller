//
// Created by Tomás Macía on 16/10/2019.
//
#include "InputPoller.h"

void InputPoller::set(Action action) {
    mu.lock();
    playerInputs.push_back(action);
    mu.unlock();
}

/*
void InputPoller::update() {
    std::list<std::tuple<Action,int>> inputs = _controller->getACopyOfNewInputs(); //obtengo una copia de todos los inputs de todos los clientes
    selectAndStoreInputsFromIncoming(inputs);
}*/

Action InputPoller::getNext() {

    Action next;

    mu.lock();
    if (!playerInputs.empty()){

        next = playerInputs.front();
        playerInputs.pop_front();
    }
    else{
        next = NONE;
    }
    mu.unlock();

    return next;
}
/*
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

        cout<<"INPUTPOLLER: "<<action<<endl;

        if (currentInputPlayerId == thisPlayerId) {
            playerInputs.push_back(currentInput);
        }
        inputs.pop_front();
    }
}
*/