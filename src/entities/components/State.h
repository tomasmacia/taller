#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "../../enumerates/Action.h"
#include "Will.h"


class State {
public:
    State(Will* will);

    void update();
    Action current();
    void setIncoming(Action incoming);
    void deactivateCorrespondingPreviousOngoingMovements(Action incoming);
    void updateMovementState(Action incoming);
    Action pickOneOngoingMovement();
    void setFinished();

    bool currentIsNotBlockingAction();
    bool isBlockingAction(Action action);
    bool isNotBlockingAction(Action action);
    bool isEndOfMovement(Action action);
    bool hasMovement();

    void flip();
    bool isFliped();
    bool facingRight();
    bool facingLeft();

    void setConnected();
    void setDisconnected();
    bool isDisconnected();

    void setDying();
    bool dead();

    void setBeingAttacked();

private:
    Will* _will = nullptr;

    Action _currentState = NONE;

    bool movingUp = false;
    bool movingDown = false;
    bool movingLeft = false;
    bool movingRight = false;

    bool _facingLeft = false;

    bool disconnected = false;

};


#endif //GAME_STATE_H
