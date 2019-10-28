#ifndef GAME_STATECOMPONENT_H
#define GAME_STATECOMPONENT_H

#include "Action.h"
#include "ECS.h"

class StateComponent : public Component {
public:

    void update() override;

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
    bool jumping();
    void setJumping();
    bool changed();

private:
    Action _currentState = NONE;
    Action _prevState = NONE;
    bool _facingLeft = false;
    bool _jumping = false;
    bool _requestForStateChange = false;

};


#endif //GAME_STATECOMPONENT_H