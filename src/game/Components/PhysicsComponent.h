#ifndef GAME_PHYSICSCOMPONENT_H
#define GAME_PHYSICSCOMPONENT_H

#include "../../to_remove_or_modify/ECS.h"
#include "../../enumerates/Action.h"
#include <list>
#include "../GameServer.h"
#include "../../to_remove_or_modify/LevelLimits.h"

class PhysicsComponent : public Component {
public:
    PhysicsComponent(LevelLimits* levelLimits);

    void update() override;
    void init() override;

    int getWalkingSpeed();
    void endJumpingMovement();
    void drag();

protected:
    void handleIncomingAction();

private:

    LevelLimits* _levelLimits = nullptr;

    float _velocityX;
    float _velocityY;
    float _accelerationX;
    float _accelerationY;

    float DEFAULT_WALKING_VELOCITY_X = ((GameServer::getInstance().getConfig()->screenResolution.width)/100);
    float DEFAULT_WALKING_VELOCITY_Y = ((GameServer::getInstance().getConfig()->screenResolution.width)/100);;

    float DEFAULT_JUMPING_ACCELERATION_Y; //setted later to sync with sprites
    float DEFAULT_JUMPING_VELOCITY_Y = ((GameServer::getInstance().getConfig()->screenResolution.height)/110);;
    //how high is the jump

    int _berforeJumpingY;

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

    void seekToSyncJumping();
};

#endif //GAME_PHYSICSCOMPONENT_H
