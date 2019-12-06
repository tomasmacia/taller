#include "State.h"

#include <iostream>

State::State(Will* will){
    _will = will;
}

void State::update(){
    auto incoming = _will->getNext();
    setIncoming(incoming);
}

void State::setIncoming(Action incoming){
    std::cout<<"incoming: "<<incoming<<std::endl;

    updateMovementState(incoming);
    handleNewState(incoming);
}

void State::handleNewState(Action incoming) {

    updateMovementState(incoming);
    updateFacingState(incoming);

    if (isEndOfMovement(_currentState) || _currentState == NONE){
        _currentState = incoming;
    }

    if (isAMovement(_currentState)){

        if (incoming != NONE){
            _currentState = incoming;
        }
        if (isEndOfMovement(incoming)) {
            restoreMovementFromOngoing(incoming);
        }
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
            break;
        case RIGHT:
            movingRight = true;
            break;
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

void State::restoreMovementFromOngoing(Action incoming) {

    _currentState = incoming;

    switch (incoming){
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
        case END_RIGHT:
            if (movingLeft){
                _currentState = LEFT;
            }
            break;
        case END_LEFT:
            if (movingRight){
                _currentState = RIGHT;
            }
            break;
    }
}

void State::updateFacingState(Action incoming) {
    switch (incoming){
        case RIGHT:
            if (facingLeft()){
                flip();
            }
            break;
        case LEFT:
            if (facingRight()){
                flip();
            }
            break;
    }
}

Action State::pickOneOngoingMovement(){

    if (movingRight){
        return RIGHT;
    }
    if (movingLeft){
        return LEFT;
    }
    if (movingDown){
        return DOWN;
    }
    if (movingUp){
        return UP;
    }
    else{
        return NONE;
    }
}

bool State::currentIsNotBlockingAction(){
    return isNotBlockingAction(_currentState);
}

bool State::isNotBlockingAction(Action action){
    return !isBlockingAction(action);
}

bool State::isBlockingAction(Action action){
    return  (action == JUMP || action == PUNCH ||
            action == KICK || action == JUMP_KICK ||
            action == CROUCH || action == DYING || action == DEAD || action == BEING_ATTACKED);
}

bool State::isEndOfMovement(Action action){
    return ((action == END_UP) || (action == END_DOWN) ||
            (action == END_LEFT) || (action == END_RIGHT));
}

bool State::isAMovement(Action action){
    return ((action == UP) || (action == DOWN) ||
            (action == LEFT) || (action == RIGHT));
}

bool State::hasMovement(){
    return (movingUp || movingDown || movingLeft || movingRight);
}

void State::setFinished(){

    if (isBlockingAction(_currentState)){

        if (_currentState == DYING || _currentState == DEAD){
            _currentState = DEAD;
        }
        else {
            _currentState = pickOneOngoingMovement();
        }
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

bool State::isFliped() {
    return _facingLeft;
}

void State::setDying() {
    _currentState = DYING;
}

bool State::dead() {
    return _currentState == DEAD;
}

void State::setBeingAttacked() {
    _currentState = BEING_ATTACKED;
}
