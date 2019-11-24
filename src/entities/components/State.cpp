#include "State.h"

State::State(Will* will){
    _will = will;
}

void State::update(){
    auto incoming = _will->getNext();
    setIncoming(incoming);
}

void State::setIncoming(Action incoming){

    if (isEndOfMovement(incoming)){
        deactivateCorrespondingPreviousOngoingMovements(incoming);
    }

    if (isBlockingAction(_currentState)){
        //pass
    }
    else{
        updateMovementState(incoming);
        _currentState = incoming;
    }
}

void State::deactivateCorrespondingPreviousOngoingMovements(Action incoming){
    switch (incoming){
        case END_UP:
            movingUp = false;
            break;
        case END_DOWN:
            movingDown = false;
            break;
        case END_LEFT:
            movingLeft = false;
            break;
        case END_RIGHT:
            movingRight = false;
            break;
    }
}

void State::updateMovementState(Action incoming){

    switch (incoming){
        case UP:
            movingUp = true;
            break;
        case DOWN:
            movingDown = true;
            break;
        case LEFT:
            movingLeft = true;
            if (facingRight()){
                flip();
            }
            break;
        case RIGHT:
            movingRight = true;
            if (facingLeft()){
                flip();
            }
            break;
        case END_UP:
            if (movingDown){
                _currentState = DOWN;
            }
            break;
        case END_DOWN:
            if (movingUp){
                _currentState = UP;
            }
            break;
        case END_LEFT:
            if (movingRight){
                _currentState = RIGHT;
            }
            break;
        case END_RIGHT:
            if (movingLeft){
                _currentState = LEFT;
            }
            break;
        default:
            //pass
            break;
    }
}

bool State::isNotBlockingAction(Action action){
    return !(action == JUMP || action == PUNCH ||
            action == KICK || action == JUMP_KICK ||
            action == CROUCH);
}

bool State::isBlockingAction(Action action){
    return  (action == JUMP || action == PUNCH ||
            action == KICK || action == JUMP_KICK ||
            action == CROUCH);
}

bool State::isEndOfMovement(Action action){
    return ((action == END_UP) || (action == END_DOWN) ||
            (action == END_LEFT) || (action == END_RIGHT));
}

bool State::hasMovement(){
    return (movingUp || movingDown || movingLeft || movingRight);
}

void State::finishBlockingState(){

    if (isBlockingAction(_currentState)){
        _currentState = NONE;
    }
}

void State::flip() {
    _facingLeft = !_facingLeft;
}

bool State::facingRight(){
    return !_facingLeft;
}

bool State::facingLeft(){
    return _facingLeft;
}

Action State::current(){
    return _currentState;
}

void State::setDisconnected() {
    disconnected = true;
}

void State::setConnected() {
    disconnected = false;
}

bool State::isDisconnected() {
    return disconnected;
}