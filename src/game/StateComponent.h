//
// Created by Tomás Macía on 14/10/2019.
//

#ifndef GAME_STATECOMPONENT_H
#define GAME_STATECOMPONENT_H

#include "ECS.h"

class StateComponent : public Component {
public:
    StateComponent(Entity *camera);
    ~StateComponent(){}

    void init() override;
    void update() override;
    void render() override;

private:
};


#endif //GAME_STATECOMPONENT_H
