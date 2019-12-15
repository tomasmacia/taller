#ifndef GAME_PHYSICS_H
#define GAME_PHYSICS_H

#include "../../enumerates/Action.h"
#include "State.h"
#include "Position.h"

class Physics {
public:
    Physics(State* state, Position* position, int walkingSpeed, int jumpingSpeed);

    void update();
    void init();
    void drag();

    int getWalkingSpeed();

protected:
    void handleCurrentState();

private:

    State* _state = nullptr;
    Position* _position = nullptr;

    float _velocityX = 0;
    float _velocityY = 0;
    float _velocityZ = 0;

    float DEFAULT_JUMPING_ACCELERATION_Y = -1;
    float DEFAULT_JUMPING_VELOCITY_Y;

    float _accelerationX = 0;
    float _accelerationY = DEFAULT_JUMPING_ACCELERATION_Y;
    float _accelerationZ = 0;

    float DEFAULT_WALKING_VELOCITY_X;
    float DEFAULT_WALKING_VELOCITY_Z;

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

    bool alreadyJumping = false;
};

#endif //GAME_PHYSICS_H
