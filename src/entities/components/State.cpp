#include "State.h"

#include <iostream>


State::State(Will* will){
    _will = will;
}

void State::update(){
    auto incoming = _will->getNext();
    //printState(incoming);
    setIncoming(incoming);
}

void State::setIncoming(Action incoming){

    updateMovementState(incoming);
    updateFacingState(incoming);;
    handleNewState(incoming);
}

void State::handleNewState(Action incoming) {

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

void State::printState(Action incoming) {

    switch (_currentState){

        case NONE:
            //std::cout<<"NONE"<<std::endl;
            break;
        case UP:
            std::cout<<"UP"<<std::endl;
            break;
        case END_UP:
            std::cout<<"END_UP"<<std::endl;
            break;
        case DOWN:
            std::cout<<"DOWN"<<std::endl;
            break;
        case END_DOWN:
            std::cout<<"END_DOWN"<<std::endl;
            break;
        case LEFT:
            std::cout<<"LEFT"<<std::endl;
            break;
        case END_LEFT:
            std::cout<<"END_LEFT"<<std::endl;
            break;
        case RIGHT:
            std::cout<<"RIGHT"<<std::endl;
            break;
        case END_RIGHT:
            std::cout<<"END_RIGHT"<<std::endl;
            break;
        case JUMP:
            std::cout<<"JUMP"<<std::endl;
            break;
        case PUNCH:
            std::cout<<"PUNCH"<<std::endl;
            break;
        case KICK:
            std::cout<<"KICK"<<std::endl;
            break;
        case JUMP_KICK:
            std::cout<<"JUMP_KICK"<<std::endl;
            break;
        case CROUCH:
            std::cout<<"CROUCH"<<std::endl;
            break;
        case BEING_ATTACKED:
            std::cout<<"BEING_ATTACKED"<<std::endl;
            break;
        case DYING:
            std::cout<<"DYING"<<std::endl;
            break;
        case DEAD:
            std::cout<<"DEAD"<<std::endl;
            break;
        case QUIT:
            std::cout<<"QUIT"<<std::endl;
            break;
    }
}
