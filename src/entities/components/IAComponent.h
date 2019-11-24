#ifndef GAME_IACOMPONENT_H
#define GAME_IACOMPONENT_H

#include "../../to_remove_or_modify/ECS.h"
#include "../../enumerates/Action.h"
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
    int side = 1;
};

#endif //GAME_IACOMPONENT_H
