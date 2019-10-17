//
// Created by Tomás Macía on 14/10/2019.
//
#include "PositionComponent.h"

PositionComponent::PositionComponent(Entity *camera) {
    this->camera = camera;
}

PositionComponent::PositionComponent(Entity *camera, int x, int y) {
    this->camera = camera;
    setPosition(x,y);
}