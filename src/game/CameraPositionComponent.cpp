//
// Created by Tomás Macía on 14/10/2019.
//

#include "CameraPositionComponent.h"
#include "PositionComponent.h"
#include <string>
#include <iostream>


void CameraPositionComponent::update() {
    PositionComponent* playerPositionComponent = player.getComponent<PositionComponent>();

    if (shouldMoveCamera(playerPositionComponent->getX())) {
        moveCamera(5);
    }

    std::cout << std::string("[CAMERA]: X inicial es ") + std::to_string(this->currentX) << std::endl;
}

bool CameraPositionComponent::shouldMoveCamera(int characterX) {
    // when character surpass camera limit with margin and character is not at the end of level
    return characterX >= (currentX + windowWidth - marginWidth) && levelWidth > (currentX + windowWidth);
}

void CameraPositionComponent::moveCamera(int amountX) {
    this->currentX += amountX;
}