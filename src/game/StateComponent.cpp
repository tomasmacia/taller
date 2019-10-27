#include "StateComponent.h"
#include "PhysicsComponent.h"

void StateComponent::update(){ //ESTE METODO TIENE QUE EJECUTARSE AL FINAL DE LOS COMPONENTS UPDATES

    if (!_requestForStateChange)
        _prevState = _currentState;
    else// si hubo request
        _requestForStateChange = false; //la reinicio

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

bool StateComponent::currentIsblockingAction(){
    return  (_currentState == JUMP || _currentState == PUNCH ||
             _currentState == KICK || _currentState == JUMP_KICK ||
             _currentState == CROUCH);
}

void StateComponent::setIncomingAction(Action action){ //cambia el estado (Por InputComponent)

    if (currentIsNotBlockingAction()){
        _prevState = _currentState;
        _currentState = action;
    }
}

void StateComponent::setJumping(){
    _jumping = true;
}

void StateComponent::setFinished(){ //cambia el estado (por RenderComponent)

    if (_jumping){
        _jumping = false;
        _requestForStateChange = true;
    }

    if (currentIsblockingAction()){
        _prevState = _currentState;
        _currentState = NONE;
        _requestForStateChange = true;
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