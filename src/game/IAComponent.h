#ifndef GAME_IACOMPONENT_H
#define GAME_IACOMPONENT_H

#include "ECS.h"
#include "Action.h"
#include <list>

class IAComponent : public Component {
public:
    IAComponent();
    void update() override;

private:
    Action generateAction();

    Action _currentAction = NONE;
    int CHOOSING_ACTION_DELAY = 50;
    int counter = 0;
};

#endif //GAME_IACOMPONENT_H
