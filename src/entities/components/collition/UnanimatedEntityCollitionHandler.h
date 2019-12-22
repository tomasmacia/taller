//
// Created by axelmpm on 2/12/19.
//

#ifndef GAME_UNANIMATEDENTITYCOLLITIONHANDLER_H
#define GAME_UNANIMATEDENTITYCOLLITIONHANDLER_H


#include "CollitionBox.h"
#include "CollitionHandler.h"

class UnanimatedEntityCollitionHandler : public CollitionHandler {

public:
    UnanimatedEntityCollitionHandler(CollitionManager *collitionManager, CollitionBox *collitionBox);

private:

    CollitionBox* _blockingCollitionBox = nullptr;

};


#endif //GAME_UNANIMATEDENTITYCOLLITIONHANDLER_H
