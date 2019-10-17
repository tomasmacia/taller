//
// Created by Axel on 15/10/2019.
//
#include <iostream>
#include "PhysicsComponent.h"
#include "../LogLib/LogManager.h"
#include "PositionComponent.h"
#include "StateComponent.h"
#include "RenderComponent.h"

void PhysicsComponent::init() {
    none(); //estado neutro (no hace nada)
}

void PhysicsComponent::update() {

    auto state = entity->getComponent<StateComponent>();

    if (state->changed()){
        handleIncomingAction();
    }
    /*
    std::cout << "============================\n";
    std::cout << "y: "<< entity->getComponent<PositionComponent>()->getY() <<"\n";
    std::cout << "_velocityY: "<< _velocityY <<"\n";
    std::cout << "_accelerationY: "<< _accelerationY <<"\n";
    std::cout << "jumping: "<< !state->notJumping() <<"\n";
    std::cout << "physics: "<< state->current() <<"\n";*/

    _velocityX += _accelerationX;
    _velocityY += _accelerationY;

    auto positionComponent = entity->getComponent<PositionComponent>();

    positionComponent->setPosition(
            (int)((float)positionComponent->getX() + _velocityX),
            (int)((float)positionComponent->getY() - _velocityY) //resto porque el SDL tiene el eje Y al revez
            );
}

void PhysicsComponent::handleIncomingAction(){
    auto state = entity->getComponent<StateComponent>();
    
    if (state->notJumping()){           //esto no es si la action actual es JUMP o JUMP_KICK
        switch (state->current()) {
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
            case JUMP:
                state->setJumping(); //la fisica es la que determina CUANDO EMPIEZA a saltar, no State
                jump();
                break;
            case PUNCH:
                punch();
                break;
            case KICK:
                kick();
                break;
            case JUMP_KICK:
                state->setJumping(); //la fisica es la que determina CUANDO EMPIEZA a saltar, no State
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

void PhysicsComponent::up() {
    _accelerationX = 0;
    _accelerationY = 0;
    _velocityY = DEFAULT_WALKING_VELOCITY_Y;
}

void PhysicsComponent::down() {
    _accelerationX = 0;
    _accelerationY = 0;
    _velocityY = -DEFAULT_WALKING_VELOCITY_Y;;
}

void PhysicsComponent::left() {
    _accelerationX = 0;
    _accelerationY = 0;
    _velocityX = -DEFAULT_WALKING_VELOCITY_X;
}

void PhysicsComponent::right() {
    _accelerationX = 0;
    _accelerationY = 0;
    _velocityX = DEFAULT_WALKING_VELOCITY_X;
}

void PhysicsComponent::jump() {
    seekToSyncJumping();
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
    seekToSyncJumping();
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

void PhysicsComponent::seekToSyncJumping(){
    int jumpDuration = entity->getComponent<RenderComponent>()->getJumpDuration();
    DEFAULT_JUMPING_ACCELERATION_Y = -2*(DEFAULT_JUMPING_VELOCITY_Y/jumpDuration);
}

