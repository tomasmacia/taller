//
// Created by axelmpm on 28/11/19.
//

#ifndef GAME_SCREENCOLLITIONHANDLER_H
#define GAME_SCREENCOLLITIONHANDLER_H

#include "CollitionHandler.h"
#include "../../../game/CollitionManager.h"
#include "../../Screen.h"

class ScreenCollitionHandler : public CollitionHandler{

public:
    ScreenCollitionHandler(CollitionManager *collitionManager, Screen *screen, bool visual);

private:
    CollitionBox* _leftScreenCollitionBox = nullptr;
    CollitionBox* _rightScreenCollitionBox = nullptr;

    int DEFAULT_SCREEN_COLLITION_BOX_WIDTH = 10;
};


#endif //GAME_SCREENCOLLITIONHANDLER_H
