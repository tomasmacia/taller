//
// Created by Axel on 15/10/2019.
//

#include "PhysicsComponent.h"
#include "../LogLib/LogManager.h"
#include "PositionComponent.h"

void PhysicsComponent::init() {
    none(); //estado neutro (no hace nada)
}

void PhysicsComponent::update() {

    if (actionIsOver()) {
        _action = NONE;
        none();
        _actionCounter = 0;
    }

    _velocityX += _accelerationX;
    _velocityY += _accelerationY;

    auto &positionComponent = entity->getComponent<PositionComponent>();

    positionComponent.setPosition(
            (int)((float)positionComponent.getX() + _velocityX),
            (int)((float)positionComponent.getY() + _velocityY)
            );

    if (_action != NONE)
        _actionCounter++;
}


void PhysicsComponent::switchAction(Action action){

    if (_action ==  NONE) {  // si hay una accion que no es NONE no se cambia
        _action = action;
        switch (action) {
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
            default:
                LogManager::logDebug("Default Action detected in physics");
                break;
        }
    }
}

bool PhysicsComponent::actionIsOver(){

    if (_action !=  NONE) {
        switch (_action) {
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
            default:
                return true; // or false ?
        }
    } else {
        return false;
    }
}

void PhysicsComponent::up() {
    _accelerationX = 0;
    _accelerationY = 0;
    _velocityX = 0;
    _velocityY = DEFAULT_WALKING_VELOCITY_Y;
}

void PhysicsComponent::down() {
    _accelerationX = 0;
    _accelerationY = 0;
    _velocityX = 0;
    _velocityY = -DEFAULT_WALKING_VELOCITY_Y;
}

void PhysicsComponent::left() {
    _accelerationX = 0;
    _accelerationY = 0;
    _velocityX = -DEFAULT_WALKING_VELOCITY_X;
    _velocityY = 0;
}

void PhysicsComponent::right() {
    _accelerationX = 0;
    _accelerationY = 0;
    _velocityX = DEFAULT_WALKING_VELOCITY_X;
    _velocityY = 0;
}

void PhysicsComponent::jump() {
    _accelerationX = 0;
    _accelerationY = DEFAULT_JUMPING_ACCELERATION_Y;
    _velocityX = _velocityX; //aca esta la inercia horizontal. La velocidad ahora es la de antes TODO no tiene sentido, se puede borrar esta linea
    _velocityY = DEFAULT_JUMPING_VELOCITY_Y;
}

void PhysicsComponent::punch() {
    _accelerationX = 0;
    _accelerationY = 0;
    _velocityX = 0;
    _velocityY = 0;
}

void PhysicsComponent::kick() {
    _accelerationX = 0;
    _accelerationY = 0;
    _velocityX = 0;
    _velocityY = 0;
}

void PhysicsComponent::jumpKick() {
    _accelerationX = 0;
    _accelerationY = DEFAULT_JUMPING_ACCELERATION_Y;
    _velocityX = _velocityX; //aca esta la inercia horizontal. La velocidad ahora es la de antes TODO no tiene sentido, se puede borrar esta linea
    _velocityY = DEFAULT_JUMPING_VELOCITY_Y;
}

void PhysicsComponent::crouch() {
    _accelerationX = 0;
    _accelerationY = 0;
    _velocityX = 0;
    _velocityY = 0;
}

void PhysicsComponent::none() {
    _accelerationX = 0;
    _accelerationY = 0;
    _velocityX = 0;
    _velocityY = 0;
}
