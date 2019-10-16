//
// Created by Tomás Macía on 14/10/2019.
//

#include "PositionComponent.h"
#include <iostream>
#include <string>
#include <list>
#include "Action.h"
#include "Game.h"

PositionComponent::PositionComponent(Entity *camera) {
    this->camera = camera;
}

void PositionComponent::update() {
    //std::cout << std::string("[POSITION]: ") + std::to_string(this->x) + ", " + std::to_string(this->y) << std::endl;
}



