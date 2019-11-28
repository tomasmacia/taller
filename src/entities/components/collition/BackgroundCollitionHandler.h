//
// Created by axel on 28/11/19.
//

#ifndef GAME_BACKGROUNDCOLLITIONHANDLER_H
#define GAME_BACKGROUNDCOLLITIONHANDLER_H


#include "CollitionBox.h"

class BackgroundCollitionHandler {

public:
    BackgroundCollitionHandler(CollitionManager *collitionManager, list<CollitionBox*>* collitionBoxes);
    ~BackgroundCollitionHandler();

private:
    list<CollitionBox*>* _collitionBoxes = nullptr;

    CollitionManager* _collitionManager = nullptr;

};
#endif //GAME_BACKGROUNDCOLLITIONHANDLER_H
