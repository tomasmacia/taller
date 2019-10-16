#ifndef GAME_STATECOMPONENT_H
#define GAME_STATECOMPONENT_H

#include "Action.h"
#include "ECS.h"

class StateComponent : public Component {
public:
    bool notBlockingAction();
    void set(Action action);
    Action current();
    bool isFlipped();
    void setFliped();
    bool facingRight();
    bool facingLeft();

private:
    Action _currentState = NONE;
    bool _fliped = false;
    bool _facingLeft = false;
};


#endif //GAME_STATECOMPONENT_H
