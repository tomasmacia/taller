//
// Created by Tomás Macía on 14/10/2019.
//

#include "CameraPositionComponent.h"
#include "PositionComponent.h"
#include <string>
#include <iostream>


void CameraPositionComponent::update() {
    if (shouldMoveCamera()){
        scroll();
    }
    //std::cout << std::string("[CAMERA]: X inicial es ") + std::to_string(this->currentX) << std::endl;
}

bool CameraPositionComponent::shouldMoveCamera() {
    return (noPlayerInLeftLimit() && marginSurpased());
}

bool CameraPositionComponent::noPlayerInLeftLimit() {

    for (auto* player : _players){
        if (inLeftLimit(player)){return false;}
    }
    return true;
}

bool CameraPositionComponent::inLeftLimit(Entity* player) {
    return (player->getComponent<PositionComponent>()->getX() <= currentX);
}

bool CameraPositionComponent::marginSurpased() {
    for (auto& player : _players){
        if (touchingMargin(player)){return true;}
    }
    return false;
}

bool CameraPositionComponent::touchingMargin(Entity* player) {
    return (player->getComponent<PositionComponent>()->getX() >= (currentX + windowWidth - marginWidth));
}

void CameraPositionComponent::scroll() {
    this->currentX += SCROLL_AMOUNT;
}

void CameraPositionComponent::setPlayer(Entity* player){
    _players.push_back(player); 
}