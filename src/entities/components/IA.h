#ifndef GAME_IA_H
#define GAME_IA_H

#include "../../enumerates/Action.h"
#include "Will.h"
#include <list>

class IA : public Will {
public:
    IA();
    void update() override;
    Action getNext() override ;

private:

    Action _currentAction = NONE;
    int CHOOSING_ACTION_DELAY = 50;
    int counter = 0;
    int side = 1;
};

#endif //GAME_IA_H
