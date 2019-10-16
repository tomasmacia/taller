#include "StateComponent.h"
#include "PhysicsComponent.h"

bool StateComponent::currentIsNotBlockingAction(){
    return !(_currentState == JUMP || _currentState == PUNCH ||
             _currentState == KICK || _currentState == JUMP_KICK ||
             _currentState == CROUCH);
}

bool StateComponent::currentIsblockingAction(){
    return  (_currentState == JUMP || _currentState == PUNCH ||
             _currentState == KICK || _currentState == JUMP_KICK ||
             _currentState == CROUCH);
}

void StateComponent::setIncomingAction(Action action){

    if (currentIsNotBlockingAction())
        _currentState = action;

    if (_currentState == JUMP || _currentState == JUMP_KICK )
        _jumping = true;
}

void StateComponent::setFinished(){

    if (_jumping)
        _jumping = false;

    if (currentIsblockingAction()){
        _currentState = NONE;
    }

}

bool StateComponent::notJumping(){
    return !_jumping;
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