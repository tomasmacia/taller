//
// Created by Tomás Macía on 15/10/2019.
//

#ifndef GAME_PHYSICSCOMPONENT_H
#define GAME_PHYSICSCOMPONENT_H

#include "ECS.h"
#include "Action.h"
#include <list>

class PhysicsComponent : public Component {
public:
    PhysicsComponent() {};

    void update() override;
    void init() override;

protected:
    void handleIncomingAction();

private:

    float _velocityX;
    float _velocityY;
    float _accelerationX;
    float _accelerationY;

    float DEFAULT_WALKING_VELOCITY_X = 4;
    float DEFAULT_WALKING_VELOCITY_Y = 4;

    float DEFAULT_JUMPING_ACCELERATION_Y = -1;
    float DEFAULT_JUMPING_VELOCITY_Y = 3;

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

    bool actionIsOver();
};

#endif //GAME_PHYSICSCOMPONENT_H
