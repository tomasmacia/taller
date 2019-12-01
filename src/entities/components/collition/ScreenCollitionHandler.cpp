//
// Created by axelmpm on 28/11/19.
//

#include "ScreenCollitionHandler.h"

ScreenCollitionHandler::ScreenCollitionHandler(Screen* screen, CollitionManager *collitionManager) {

    _collitionManager = collitionManager;

    _leftScreenCollitionBox = collitionManager->addBlockingCollitionBox(0, 0, 0, -1, screen->getWindowHeight(),
                                                                         screen->getLevelDepth());
    _rightScreenCollitionBox = collitionManager->addBlockingCollitionBox(screen->getWindowWidth(), 0, 0, -1,
                                                                         screen->getWindowHeight(), screen->getLevelDepth());
    _leftScreenCollitionBox->setOwner((Entity*)screen);
    _rightScreenCollitionBox->setOwner((Entity*)screen);

    _collitionBoxes->push_back(_leftScreenCollitionBox);
    _collitionBoxes->push_back(_rightScreenCollitionBox);
}
