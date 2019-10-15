#include "PhysicsComponent.h"

PhysicsComponent::PhysicsComponent(int x, int y){
    _x = x;
    _y = y;
    none(); //estado neutro (no hace nada)
}

void PhysicsComponent::update(){

    if (actionIsOver()){
        _action = NONE;
        none();
        _actionCounter = 0;
    }

    _velocityX += _accelerationX;
    _velocityY += _accelerationY;

    _x += _velocityX;
    _y += _velocityY;

    /*
    if (ifXOutOfRange()){
        _x -= _velocityX;
    }
    if (ifYOutOfRange()){
        _y -= _velocityY;
    }
    */

    if (_action != NONE)
        _actionCounter++;
}

/*
bool PhysicsComponent::ifXOutOfRange(){
    return Game::->ifXOutOfRange(_x);
}

//_x > Game::->maxX() || _x < Game::->minX();

bool PhysicsComponent::ifYOutOfRange(){
    return Game::->ifYOutOfRange(_y);
}
*/

int PhysicsComponent::getX(){
    return _x;
}

int PhysicsComponent::getY(){
    return _y;
}

void PhysicsComponent::switchAction(Action action){

    if (_action ==  NONE){  //si hay una accion que no es NONE no se cambia
        _action = action;
        switch (action)
        {
        case UP:
            up();
            break;
        case DOWN:
            down();
            break;
        case LEFT:
            left();
            break;
        case RIGHT:
            right();
            break;
        case JUMP:
            jump();
            break;
        case PUNCH:
            punch();
            break;
        case KICK:
            kick();
            break;
        case JUMP_KICK:
            jumpKick();
            break;
        case CROUCH:
            crouch();
            break;
    }
    }
}

bool PhysicsComponent::actionIsOver(){

    if (_action !=  NONE){
        switch (_action)
        {
        case UP:
            return _actionCounter >= UP_TICKS;
        case DOWN:
            return _actionCounter >= DOWN_TICKS;
        case LEFT:
            return _actionCounter >= LEFT_TICKS;
        case RIGHT:
            return _actionCounter >= RIGHT_TICKS;
        case JUMP:
            return _actionCounter >= JUMP_TICKS;
        case PUNCH:
            return _actionCounter >= PUNCH_TICKS;
        case KICK:
            return _actionCounter >= KICK_TICKS;
        case JUMP_KICK:
            return _actionCounter >= JUMP_KICK_TICKS;
        case CROUCH:
            return _actionCounter >= CROUCH_TICKS;
        }
    }
    else{
        return false;
    }
}

void PhysicsComponent::up(){
    _accelerationX = 0;
    _accelerationY = 0;
    _velocityX = 0;
    _velocityY = DEFAULT_WALKING_VELOCITY_Y;
}

void PhysicsComponent::down(){
    _accelerationX = 0;
    _accelerationY = 0;
    _velocityX = 0;
    _velocityY = -DEFAULT_WALKING_VELOCITY_Y;
}

void PhysicsComponent::left(){
    _accelerationX = 0;
    _accelerationY = 0;
    _velocityX = -DEFAULT_WALKING_VELOCITY_X;
    _velocityY = 0;
}

void PhysicsComponent::right(){
    _accelerationX = 0;
    _accelerationY = 0;
    _velocityX = DEFAULT_WALKING_VELOCITY_X;
    _velocityY = 0;
}

void PhysicsComponent::jump(){
    _accelerationX = 0;
    _accelerationY = DEFAULT_JUMPING_ACCELERATION_Y;
    _velocityX = _velocityX; //aca esta la inercia horizontal. La velocidad ahora es la de antes
    _velocityY = DEFAULT_JUMPING_VELOCITY_Y;
}

void PhysicsComponent::punch(){
    _accelerationX = 0;
    _accelerationY = 0;
    _velocityX = 0;
    _velocityY = 0;  
}

void PhysicsComponent::kick(){
    _accelerationX = 0;
    _accelerationY = 0;
    _velocityX = 0;
    _velocityY = 0;
}

void PhysicsComponent::jumpKick(){
    _accelerationX = 0;
    _accelerationY = DEFAULT_JUMPING_ACCELERATION_Y;
    _velocityX = _velocityX; //aca esta la inercia horizontal. La velocidad ahora es la de antes
    _velocityY = DEFAULT_JUMPING_VELOCITY_Y; 
}

void PhysicsComponent::crouch(){
    _accelerationX = 0;
    _accelerationY = 0;
    _velocityX = 0;
    _velocityY = 0;
}

void PhysicsComponent::none(){
    _accelerationX = 0;
    _accelerationY = 0;
    _velocityX = 0;
    _velocityY = 0;
}