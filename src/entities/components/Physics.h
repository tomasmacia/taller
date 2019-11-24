#ifndef GAME_PHYSICS_H
#define GAME_PHYSICS_H

#include "../../enumerates/Action.h"
#include "State.h"
#include "Position.h"

class Physics {
public:
    Physics(State* state, Position* position);

    void update();
    void init();
    void drag();

protected:
    void handleCurrentState();

private:

    State* _state = nullptr;
    Position* _position = nullptr;

    float _velocityX;
    float _velocityY;
    float _velocityZ;

    float _accelerationX;
    float _accelerationY;
    float _accelerationZ;

    float DEFAULT_WALKING_VELOCITY_X;
    float DEFAULT_WALKING_VELOCITY_Z;

    float DEFAULT_JUMPING_ACCELERATION_Y = 10;
    float DEFAULT_JUMPING_VELOCITY_Y = 10;          //how high is the jump

    void up();
    void down();
    void left();
    void right();
    void jump();
    void punch();
    void kick();
    void jumpKick();
    void crouch();
    void none();

    void endUp();
    void endDown();
    void endLeft();
    void endRight();
};

#endif //GAME_PHYSICS_H
