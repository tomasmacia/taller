//
// Created by Tomás Macía on 16/10/2019.
//

#ifndef GAME_INPUTCOMPONENT_H
#define GAME_INPUTCOMPONENT_H

#include "ECS.h"
#include "Action.h"
#include <list>


class InputComponent : public Component {
public:
    void update() override;

    std::list<Action> getActions() {
        return actions;
    }

private:
    std::list<Action> actions;
};


#endif //GAME_INPUTCOMPONENT_H