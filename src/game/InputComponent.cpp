#include "InputComponent.h"

InputComponent::InputComponent(Controller* controller, Character* character){
    _controller = controller;
    _character = character;
}

void InputComponent::update(){

    _actions = _controller->getInput();

    if (!_actions.empty()){
        Action action = _actions.back();
        _actions.pop_back();

        if (action != NONE && action != QUIT)
            _character->setAction(action);
    }
}