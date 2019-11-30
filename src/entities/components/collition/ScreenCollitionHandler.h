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
    ScreenCollitionHandler(Screen* screen, CollitionManager* collitionManager);

private:
    CollitionBox* _leftScreenCollitionBox = nullptr;
    CollitionBox* _rightScreenCollitionBox = nullptr;
};


#endif //GAME_SCREENCOLLITIONHANDLER_H
