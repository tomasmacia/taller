#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "../../enumerates/Action.h"
#include "Will.h"
#include "../../enumerates/AttackCode.h"

class State {
public:
    State(Will* will);

    void update();
    Action current();
    void setIncoming(Action incoming);
    void updateMovementState(Action incoming);
    void restoreMovementFromOngoing(Action incoming);
    Action pickOneOngoingMovement();
    void setFinished();

    bool currentIsNotBlockingAction();
    bool isBlockingAction(Action action);
    bool isNotBlockingAction(Action action);
    bool isEndOfMovement(Action action);
    bool isAMovement(Action action);
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
    void endBeingAttacked();
    void setBeingAttacked();

    void handleNewState(Action action);
    void updateFacingState(Action action);
    void printState(Action action);

    void setDead();

    void equipWeapon(AttackCode weaponID);

    void dropWeapon();

    AttackCode getWeapon();

    bool isHitting();

    void setHitting();

    void endHittingFlag();

    bool justPickedWeapon();

    void endPickingFlag();

private:
    Will* _will = nullptr;

    Action _currentState = NONE;
    AttackCode _currentWeapon = NO_WEAPON;

    bool movingUp = false;
    bool movingDown = false;
    bool movingLeft = false;
    bool movingRight = false;

    bool _facingLeft = false;

    bool justHitted = false;
    bool justPicked = false;

    bool disconnected = false;
};


#endif //GAME_STATE_H
