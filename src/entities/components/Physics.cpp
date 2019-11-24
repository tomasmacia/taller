//
// Created by Axel on 15/10/2019.
//

#include "Physics.h"
#include "Position.h"
#include "State.h"

Physics::Physics(State* state, Position* position){
    _state = state;
    _position = position;
    init();
}

void Physics::init() {
    none(); //estado neutro (no hace nada)
}

void Physics::update() {

    handleCurrentState();

    int prevX = _position->getX();
    int prevY = _position->getY();
    int prevZ = _position->getZ();

    _velocityX += _accelerationX;
    _velocityY += _accelerationY;
    _velocityZ += _accelerationZ;

    int newX = (int)((float)prevX + _velocityX);
    int newY = (int)((float)prevY - _velocityY); //resto porque el SDL tiene el eje Y al revez
    int newZ = (int)((float)prevZ - _velocityZ); //resto porque el SDL tiene el eje Y al revez

    _position->ifValidChangeTo(newX,newY,newZ);
}

void Physics::handleCurrentState(){

    switch (_state->current()) {
        case NONE:
            none();
            break;
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
        case END_UP:
            endUp();
            break;
        case END_DOWN:
            endDown();
            break;
        case END_LEFT:
            endLeft();
            break;
        case END_RIGHT:
            endRight();
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

void Physics::up() {
    _accelerationX = 0;
    _velocityZ = DEFAULT_WALKING_VELOCITY_Z;
}

void Physics::down() {
    _accelerationX = 0;
    _velocityZ = -DEFAULT_WALKING_VELOCITY_Z;;
}

void Physics::left() {
    _accelerationX = 0;
    _velocityX = -DEFAULT_WALKING_VELOCITY_X;
}

void Physics::right() {
    _accelerationX = 0;
    _velocityX = DEFAULT_WALKING_VELOCITY_X;
}

void Physics::endUp() {
    _accelerationY = 0;
    _velocityY = 0;
}

void Physics::endDown() {
    _accelerationX = 0;
    _accelerationY = 0;
    _velocityY = 0;;
}

void Physics::endLeft() {
    _accelerationX = 0;
    _velocityX = 0;
}

void Physics::endRight() {
    _accelerationX = 0;
    _velocityX = 0;
}

void Physics::jump() {
    _accelerationX = 0;
    _accelerationY = DEFAULT_JUMPING_ACCELERATION_Y;
    _velocityX = _velocityX; //aca esta la inercia horizontal. La velocidad ahora es la de antes TODO no tiene sentido, se puede borrar esta linea
    _velocityY = DEFAULT_JUMPING_VELOCITY_Y;
}

void Physics::punch() {
    _accelerationX = 0;
    _accelerationY = 0;
    _velocityX = 0;
    _velocityY = 0;
}

void Physics::kick() {
    _accelerationX = 0;
    _accelerationY = 0;
    _velocityX = 0;
    _velocityY = 0;
}

void Physics::jumpKick() {
    _accelerationX = 0;
    _accelerationY = DEFAULT_JUMPING_ACCELERATION_Y;
    _velocityX = _velocityX; //aca esta la inercia horizontal. La velocidad ahora es la de antes TODO no tiene sentido, se puede borrar esta linea
    _velocityY = DEFAULT_JUMPING_VELOCITY_Y;
}

void Physics::crouch() {
    _accelerationX = 0;
    _accelerationY = 0;
    _velocityX = 0;
    _velocityY = 0;
}

void Physics::none() {
    _accelerationX = 0;
    _accelerationY = 0;
    _velocityX = 0;
    _velocityY = 0;
}

void Physics::drag(){

    int prevX = _position->getX();
    int prevY = _position->getY();
    int prevZ = _position->getZ();

    int newX = prevX + DEFAULT_WALKING_VELOCITY_X;

    _position->ifValidChangeTo(newX,prevY,prevZ);
}