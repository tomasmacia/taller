//
// Created by axelmpm on 28/11/19.
//

#include "ScreenCollitionHandler.h"

ScreenCollitionHandler::ScreenCollitionHandler(CollitionManager* collitionManager, Screen* screen) : CollitionHandler(collitionManager){

    _leftScreenCollitionBox = addBlockingCollitionBox(0,0,0,-1,screen->getWindowHeight(),screen->getLevelDepth());
    _rightScreenCollitionBox = addBlockingCollitionBox(screen->getWindowHeight(),0,0,-1,screen->getWindowHeight(),screen->getLevelDepth());
}