#ifndef GAME_COMPONENT_H
#define GAME_COMPONENT_H

#include "Action.h"

class Component {

protected:
    Action _action = NONE;
    int _actionCounter = 0;

public:    
    virtual void update() = 0;
    virtual void render() = 0;

    void setAction(Action action){
        switchAction(action);
    }

protected:
    virtual void switchAction(Action action) = 0;
};
#endif //GAME_COMPONENT_H