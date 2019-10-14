#ifndef GAME_PHYSICSCOMPONENT_H
#define GAME_PHYSICSCOMPONENT_H

#include "Component.h"
#include "Action.h"

class PhysicsComponent : public Component{

private:

    int _x;
    int _y;
    float _velocityX;
    float _velocityY;
    float _accelerationX;
    float _accelerationY;

    float DEFAULT_WAKING_VELOCITY_X = 2;
    float DEFAULT_WAKING_VELOCITY_Y = 2;

    float DEFAULT_JUMPING_VELOCITY_Y = 2; //velocidad vertical con la que el personaje salta
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

public:
    PhysicsComponent(int x, int y);
    ~PhysicsComponent();

    void update() override;
    void render() override{}

protected:
    void switchAction(Action action) override;

private:
    bool ifXOutOfRange();
    bool ifYOutOfRange();
    
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