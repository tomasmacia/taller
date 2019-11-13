#ifndef GAME_STATECOMPONENT_H
#define GAME_STATECOMPONENT_H

#include <list>

#include "Action.h"
#include "ECS.h"


class StateComponent : public Component {
public:

    void update() override;

    bool currentIsNotBlockingAction();
    Action current();
    bool isFliped();
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
    bool hasFinishedJumping();

    void saveLastNonBlockingSate();

    void addMovement(Action movement);
    void substractMovement(Action movement);
    bool hasMovement();

    void setConnected();
    void setDisconnected();
    bool isDisconnected();

private:
    Action _currentState = NONE;
    Action _prevState = NONE;
    Action _lastNonBlockingState = NONE;

    bool _facingLeft = false;
    bool _jumping = false;
    bool _requestForStateChange = false;

    std::list<Action> movements;

    bool disconnected = false;

};


#endif //GAME_STATECOMPONENT_H
