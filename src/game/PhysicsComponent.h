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

    void setIncomingAction(Action action){_incomingAction = action;}
    Action getIncoming();

protected:
    void handleIncomingAction();

private:

    float _velocityX;
    float _velocityY;
    float _accelerationX;
    float _accelerationY;

    float DEFAULT_WALKING_VELOCITY_X = 4;
    float DEFAULT_WALKING_VELOCITY_Y = 4;

    float DEFAULT_JUMPING_VELOCITY_Y = 40; // velocidad vertical con la que el personaje salta
    float DEFAULT_JUMPING_ACCELERATION_Y = -4;

    int UP_TICKS = 9;
    int DOWN_TICKS = 9;
    int LEFT_TICKS = 9;
    int RIGHT_TICKS = 9;
    int JUMP_TICKS = 13;
    int PUNCH_TICKS = 3;
    int KICK_TICKS = 6;
    int JUMP_KICK_TICKS = 13;
    int CROUCH_TICKS = 4;

    Action _incomingAction = NONE;
    int _actionCounter = 0;

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
