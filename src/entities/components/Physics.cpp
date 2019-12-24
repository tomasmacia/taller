//
// Created by Axel on 15/10/2019.
//

#include "Physics.h"
#include "Position.h"
#include "State.h"

#include <iostream>

Physics::Physics(State* state, Position* position, int walkingSpeed, int jumpingSpeed){
    _state = state;
    _position = position;

    DEFAULT_WALKING_VELOCITY_X = walkingSpeed;
    DEFAULT_WALKING_VELOCITY_Z = walkingSpeed;
    DEFAULT_JUMPING_VELOCITY_Y = jumpingSpeed;

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
    int newY = (int)((float)prevY + _velocityY);
    int newZ = (int)((float)prevZ + _velocityZ);



    Action current = _state->current();
    if (_state->isAMovement(current) || current == JUMP || current == JUMP_KICK || current == END_JUMP || stuckInTheAir){
        _position->tryToMoveTo(newX, newY, newZ);

        if (stuckInTheAir){
            stuckInTheAir = false;
        }
    }
}

void Physics::handleCurrentState(){

    if (_state->current() != JUMP && _state->current() != JUMP_KICK){
        alreadyJumping = false;
    }

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
            if (!alreadyJumping){
                prevYToJump = _position->getY();
                alreadyJumping = true;
                jump();
            }
            break;
        case PUNCH:
            punch();
            break;
        case KICK:
            kick();
            break;
        case JUMP_KICK:
            if (!alreadyJumping){
                prevYToJump = _position->getY();
                alreadyJumping = true;
                jumpKick();
            }
            break;
        case END_JUMP:
            if (_position->getY() == prevYToJump){
                none();
            }
            else{
                stuckInTheAir = true;
            }
            break;
        case CROUCH:
            crouch();
            break;
        case BEING_ATTACKED:
            none();
            break;
        case DYING:
            none();
            break;
        case DEAD:
            break;
        case QUIT:
            break;
    }
}

void Physics::up() {
    _velocityZ = DEFAULT_WALKING_VELOCITY_Z;
}

void Physics::down() {
    _velocityZ = -DEFAULT_WALKING_VELOCITY_Z;;
}

void Physics::left() {
    _velocityX = -DEFAULT_WALKING_VELOCITY_X;
}

void Physics::right() {
    _velocityX = DEFAULT_WALKING_VELOCITY_X;
}

void Physics::endUp() {
    _velocityZ = 0;
}

void Physics::endDown() {
    _velocityZ = 0;;
}

void Physics::endLeft() {
    _velocityX = 0;
}

void Physics::endRight() {
    _velocityX = 0;
}

void Physics::jump() {
    _velocityY = DEFAULT_JUMPING_VELOCITY_Y;
}

void Physics::punch() {
    _accelerationX = 0;
    _velocityX = 0;
    _velocityY = 0;
}

void Physics::kick() {
    _accelerationX = 0;
    _velocityX = 0;
    _velocityY = 0;
}

void Physics::jumpKick() {
    _velocityY = DEFAULT_JUMPING_VELOCITY_Y;
}

void Physics::crouch() {
    _accelerationX = 0;
    _velocityX = 0;
    _velocityY = 0;
}

void Physics::none() {
    _accelerationX = 0;
    _velocityX = 0;
    _velocityY = 0;
    _velocityZ = 0;
}

void Physics::drag(){

    int prevX = _position->getX();
    int prevY = _position->getY();
    int prevZ = _position->getZ();

    int newX = prevX + DEFAULT_WALKING_VELOCITY_X;

    _position->tryToMoveTo(newX, prevY, prevZ);
}

int Physics::getWalkingSpeed() {
    return DEFAULT_WALKING_VELOCITY_X;
}
