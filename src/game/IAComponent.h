#ifndef GAME_IACOMPONENT_H
#define GAME_IACOMPONENT_H

#include "ECS.h"
#include "Action.h"
#include <list>

class IAComponent : public Component {
public:
    IAComponent() {};

    void update() override;

private:
    Action generateAction();
};

#endif //GAME_IACOMPONENT_H
