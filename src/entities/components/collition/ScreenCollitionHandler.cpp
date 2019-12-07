//
// Created by axelmpm on 28/11/19.
//

#include "ScreenCollitionHandler.h"

ScreenCollitionHandler::ScreenCollitionHandler(CollitionManager *collitionManagel,
                                               CollitionManager *collitionManager, Screen *screen, bool visual)
        : CollitionHandler(collitionManagel) {

    _leftScreenCollitionBox = collitionManager->createScreenBlockingCollitionBox(0,0,0,DEFAULT_SCREEN_COLLITION_BOX_WIDTH,screen->getWindowHeight(),screen->getLevelDepth(),visual);
    _rightScreenCollitionBox = collitionManager->createScreenBlockingCollitionBox(screen->getWindowWidth(),0,0,DEFAULT_SCREEN_COLLITION_BOX_WIDTH,screen->getWindowHeight(),screen->getLevelDepth(),visual);
    _collitionBoxes->push_back(_leftScreenCollitionBox);
    _collitionBoxes->push_back(_rightScreenCollitionBox);
}
