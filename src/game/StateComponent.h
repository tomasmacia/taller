#ifndef GAME_STATECOMPONENT_H
#define GAME_STATECOMPONENT_H

#include "Action.h"
#include "ECS.h"

class StateComponent : public Component {
public:
    bool currentIsNotBlockingAction();
    Action current();
    bool isFlipped();
    void setFliped();
    bool facingRight();
    bool facingLeft();
    void setFinished();
    bool currentIsblockingAction();
    bool blockingActionFinished();
    void setIncomingAction(Action action);
    bool notJumping();

private:
    Action _currentState = NONE;
    bool _facingLeft = false;
    bool _jumping = false;
};


#endif //GAME_STATECOMPONENT_H
