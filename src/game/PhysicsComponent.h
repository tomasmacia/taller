#ifndef GAME_PHYSICSCOMPONENT_H
#define GAME_PHYSICSCOMPONENT_H

#include "ECS.h"
#include "Action.h"
#include <list>
#include "GameServer.h"
#include "LevelLimits.h"

class PhysicsComponent : public Component {
public:
    PhysicsComponent(LevelLimits* levelLimits);

    void update() override;
    void init() override;

    int getWalkingSpeed();
    void drag();

protected:
    void handleIncomingAction();

private:

    LevelLimits* _levelLimits = nullptr;

    float _velocityX;
    float _velocityY;
    float _accelerationX;
    float _accelerationY;

    float DEFAULT_WALKING_VELOCITY_X = ((GameServer::getInstance().getConfig()->screenResolution.width)/50);
    float DEFAULT_WALKING_VELOCITY_Y = ((GameServer::getInstance().getConfig()->screenResolution.width)/100);;

    float DEFAULT_JUMPING_ACCELERATION_Y; //setted later to sync with sprites
    float DEFAULT_JUMPING_VELOCITY_Y = ((GameServer::getInstance().getConfig()->screenResolution.height)/110);;
    //how high is the jump

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

    void seekToSyncJumping();
};

#endif //GAME_PHYSICSCOMPONENT_H
