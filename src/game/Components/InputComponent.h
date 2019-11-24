//
// Created by Tomás Macía on 16/10/2019.
//

#ifndef GAME_INPUTCOMPONENT_H
#define GAME_INPUTCOMPONENT_H

#include "../../to_remove_or_modify/ECS.h"
#include "../../enumerates/Action.h"
#include <list>


class InputComponent : public Component {
public:
    void update() override;
};


#endif //GAME_INPUTCOMPONENT_H
