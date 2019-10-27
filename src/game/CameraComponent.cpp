//
// Created by Tomás Macía on 14/10/2019.
//

#include <iostream>
#include <string>
#include "CameraComponent.h"
#include "PositionComponent.h"

void CameraComponent::update() {
    PositionComponent positionComponent = entity->getComponent<PositionComponent>(); // TODO move to class attr

    if (shouldMoveCamera(positionComponent.getX())) {
        moveCamera(1);
    }

    std::cout << std::string("[CAMERA]: X inicial es ") + std::to_string(this->currentX) << std::endl;
}

bool CameraComponent::shouldMoveCamera(int characterX) {
    // when character surpass camera limit with margin and character is not at the end of level
    return characterX >= (windowWidth - marginWidth) && levelWidth > (currentX + windowWidth);
}

void CameraComponent::moveCamera(int amountX) {
    this->currentX += amountX;
}