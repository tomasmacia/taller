#ifndef GAME_STATECOMPONENT_H
#define GAME_STATECOMPONENT_H

#include <list>

#include "Action.h"
#include "ECS.h"


class StateComponent : public Component {
public:

    void update() override;

    bool currentIsNotBlockingAction();
    bool incomingIsNotBlockingAction(Action incoming);
    Action current();
    bool isFliped();
    void setFliped();
    bool facingRight();
    bool facingLeft();
    void setFinished();
    bool currentIsBlockingAction();
    bool blockingActionFinished();
    void setIncomingAction(Action action);
    bool notJumping();
    bool jumping();
    void setJumping();
    bool changed();
    bool hasMovement();
    bool isEndOfMovement(Action action);

    void setConnected();
    void setDisconnected();
    bool isDisconnected();

private:
    Action _currentState = NONE;
    Action _prevState = NONE;

    bool movingUp = false;
    bool movingDown = false;
    bool movingLeft = false;
    bool movingRight = false;

    bool _facingLeft = false;
    bool _jumping = false;
    bool _requestForStateChange = false;

    bool disconnected = false;

};


#endif //GAME_STATECOMPONENT_H
