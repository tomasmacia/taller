//
// Created by axelmpm on 28/11/19.
//

#include "ScreenCollitionHandler.h"

ScreenCollitionHandler::ScreenCollitionHandler(CollitionManager *collitionManager, Screen *screen, bool visual)
        : CollitionHandler(collitionManager) {

    _leftScreenCollitionBox = collitionManager->createScreenBlockingCollitionBox(-DEFAULT_SCREEN_COLLITION_BOX_WIDTH/2,screen->getWindowHeight()/2,screen->getLevelDepth()/2,DEFAULT_SCREEN_COLLITION_BOX_WIDTH,screen->getWindowHeight(),screen->getLevelDepth(),visual);
    _rightScreenCollitionBox = collitionManager->createScreenBlockingCollitionBox(screen->getWindowWidth() + DEFAULT_SCREEN_COLLITION_BOX_WIDTH/2,screen->getWindowHeight()/2,screen->getLevelDepth()/2,DEFAULT_SCREEN_COLLITION_BOX_WIDTH,screen->getWindowHeight(),screen->getLevelDepth(),visual);
    _collitionBoxes->push_back(_leftScreenCollitionBox);
    _collitionBoxes->push_back(_rightScreenCollitionBox);
    _collitionManager->setLeftScreenBlockingCollitionBox(_leftScreenCollitionBox);
}

void ScreenCollitionHandler::resetAll(Screen *screen) {
    _leftScreenCollitionBox->setAt(DEFAULT_SCREEN_COLLITION_BOX_WIDTH/2,screen->getWindowHeight()/2,screen->getLevelDepth()/2);
    _rightScreenCollitionBox->setAt(screen->getWindowWidth() + DEFAULT_SCREEN_COLLITION_BOX_WIDTH/2,screen->getWindowHeight()/2,screen->getLevelDepth()/2);
}
