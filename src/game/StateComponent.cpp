#include <algorithm>

#include "StateComponent.h"
#include "PhysicsComponent.h"

void StateComponent::update(){ //ESTE METODO TIENE QUE EJECUTARSE AL FINAL DE LOS COMPONENTS UPDATES

    if (!_requestForStateChange)
        _prevState = _currentState;
    else// si hubo request
    {
        _requestForStateChange = false; //la reinicio
    }


    /*Esto hace que el StateComponent se "entere" de que paso un tick 
    y para que, si hubo un cambio de estado antes, en el siguiente tick deje
    de considerarlo como un cambio de estado y entienda que el de current
    es el mismo que el prev
    */
}

bool StateComponent::currentIsNotBlockingAction(){
    return !(_currentState == JUMP || _currentState == PUNCH ||
             _currentState == KICK || _currentState == JUMP_KICK ||
             _currentState == CROUCH);
}

bool StateComponent::currentIsBlockingAction(){
    return  (_currentState == JUMP || _currentState == PUNCH ||
             _currentState == KICK || _currentState == JUMP_KICK ||
             _currentState == CROUCH);
}

bool StateComponent::incomingIsNotBlockingAction(Action incoming){
    return !(incoming == JUMP || incoming == PUNCH ||
            incoming == KICK || incoming == JUMP_KICK ||
            incoming == CROUCH);
}

void StateComponent::setIncomingAction(Action action){ //cambia el estado (Por InputComponent)

    if (currentIsNotBlockingAction()){
        if (incomingIsNotBlockingAction(action)){
            switch (action){
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
                    if (movingDown){
                        action = DOWN;
                    }
                    break;
                case END_DOWN:
                    movingDown = false;
                    if (movingUp){
                        action = UP;
                    }
                    break;
                case END_LEFT:
                    movingLeft = false;
                    if (movingRight){
                        action = RIGHT;
                    }
                    break;
                case END_RIGHT:
                    movingRight = false;
                    if (movingLeft){
                        action = LEFT;
                    }
                    break;
            }
        }
        _prevState = _currentState;
        _currentState = action;
    }
    else{
        if (isEndOfMovement(action)){
            switch (action){
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
    }
}

bool StateComponent::isEndOfMovement(Action action){
    return ((action == END_UP) || (action == END_DOWN) ||
            (action == END_LEFT) || (action == END_RIGHT));

}

bool StateComponent::hasMovement(){
    return (movingUp || movingDown || movingLeft || movingRight);
}

void StateComponent::setJumping(){
    _jumping = true;
}

void StateComponent::setFinished(){ //cambia el estado (por RenderComponent)

    if (_jumping){
        _jumping = false;
        _requestForStateChange = true;
        entity->getComponent<PhysicsComponent>()->endJumpingMovement();
    }

    if (currentIsBlockingAction()){
        _prevState = _currentState;
        _currentState = NONE;
        _requestForStateChange = true;

        if (movingRight){           //es cierto que estoy priorizando unas sobre otras
            _currentState = RIGHT;
        }
        else if (movingLeft){
            _currentState = LEFT;
        }
        else if (movingUp){
            _currentState = UP;
        }
        else if (movingDown){
            _currentState = DOWN;
        }
    }
}

bool StateComponent::changed(){
    return _prevState != _currentState;
}

bool StateComponent::notJumping(){
    return !_jumping;
}

bool StateComponent::jumping(){
    return _jumping;
}

void StateComponent::setFliped(){
    _facingLeft = !_facingLeft;
}

bool StateComponent::isFliped(){
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

void StateComponent::setDisconnected() {
    disconnected = true;
}

void StateComponent::setConnected() {
    disconnected = false;
}

bool StateComponent::isDisconnected() {
    return disconnected;
}