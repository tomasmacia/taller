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

    void setActions(std::list<Action> actions);

protected:
    void handleIncomingAction();

private:
    float _velocityX;
    float _velocityY;
    float _accelerationX;
    float _accelerationY;

    float DEFAULT_WALKING_VELOCITY_X = 2;
    float DEFAULT_WALKING_VELOCITY_Y = 2;

    float DEFAULT_JUMPING_VELOCITY_Y = 2; // velocidad vertical con la que el personaje salta
    float DEFAULT_JUMPING_ACCELERATION_Y = -2;

    int UP_TICKS = 1;
    int DOWN_TICKS = 1;
    int LEFT_TICKS = 1;
    int RIGHT_TICKS = 1;
    int JUMP_TICKS = 1;
    int PUNCH_TICKS = 1;
    int KICK_TICKS = 1;
    int JUMP_KICK_TICKS = 1;
    int CROUCH_TICKS = 1;

    Action _currentAction = NONE;
    Action _incomingAction = NONE;
    std::list<Action> _actionsQueue;
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
