#include "StateComponent.h"
#include "PhysicsComponent.h"

bool StateComponent::notBlockingAction(){
    return !(_currentState == JUMP || _currentState == PUNCH ||
             _currentState == KICK || _currentState == JUMP_KICK ||
             _currentState == CROUCH);
}

void StateComponent::set(Action action){
    _currentState = action;
}

void StateComponent::setFliped(){
    _facingLeft = !_facingLeft;
}

bool StateComponent::isFlipped(){
    return _facingLeft;
}

bool StateComponent::facingRight(){
    return !_facingLeft;
}

bool StateComponent::facingLeft(){
    return _facingLeft;
}

Action StateComponent::current(){
    return _currentState;
}