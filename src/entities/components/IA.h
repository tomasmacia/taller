#ifndef GAME_IA_H
#define GAME_IA_H

#include "../../enumerates/Action.h"
#include "Will.h"
#include <list>
#include "../game/EntityManager.h"

class IA : public Will {
public:
    IA(EntityManager* em,Position* subjectPosition);
    void update() override;
    Action getNext() override;
    void changeBehavior(Will* newBehavior);

private:

    Action _currentAction = NONE;
    int CHOOSING_ACTION_DELAY = 50;
    int counter = 0;
    int side = 1;
    Will* behavior;
    EntityManager* em;
};

#endif //GAME_IA_H
