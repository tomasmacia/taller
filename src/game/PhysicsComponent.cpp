#include "PhysicsComponent.h"

PhysicsComponent::PhysicsComponent(int x, int y){
    _x = x;
    _y = y;
}

void PhysicsComponent::setVelocity(int velocity){
    _velocity = velocity;
}