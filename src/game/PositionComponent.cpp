//
// Created by Tomás Macía on 14/10/2019.
//

#include "PositionComponent.h"
#include <iostream>
#include <string>
#include <vector>
#include "Action.h"
#include "Game.h"



void PositionComponent::update() {
    std::vector<Action> actions = Game::getInstance().getController()->getInput();


    for (auto &action : actions){
        switch(action) {
            case Action::UP:
                y += 1;
                break;
            case Action::DOWN:
                y -= 1;
                break;
            case Action::LEFT:
                x -= 1;
                break;
            case Action::RIGHT:
                x += 1;
                break;
            default:
                break;
        }
    }
    std::cout << std::string("[POSITION]: ") + std::to_string(this->x) + ", " + std::to_string(this->y) << std::endl;
}

void PositionComponent::render() {

}

