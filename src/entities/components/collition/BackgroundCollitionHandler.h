//
// Created by axel on 28/11/19.
//

#ifndef GAME_BACKGROUNDCOLLITIONHANDLER_H
#define GAME_BACKGROUNDCOLLITIONHANDLER_H


#include "collitionBoxHierarchy/CollitionBox.h"

class BackgroundCollitionHandler : public CollitionHandler {

public:
    BackgroundCollitionHandler(CollitionManager *collitionManager, list<CollitionBox*>* collitionBoxes);
    ~BackgroundCollitionHandler();

};
#endif //GAME_BACKGROUNDCOLLITIONHANDLER_H
