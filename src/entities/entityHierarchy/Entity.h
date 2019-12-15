//
// Created by axel on 27/11/19.
//

#ifndef GAME_ENTITY_H
#define GAME_ENTITY_H


#include "../../net/messaging/Sendable.h"
#include "../../enumerates/AttackCode.h"
#include "../components/collition/CollitionHandler.h"

class Entity {

public:
    Entity(CollitionHandler* collitionHandler);
    Entity(){}
    virtual ~Entity();

    virtual void update() = 0;
    virtual list<Sendable*> generateSendable() = 0;

    virtual int setAttackedWith(AttackCode attack){return 0;} //returns score to attacker, by default its 0

    virtual bool isEnemy(){return false;}
    virtual bool isFinalBoss(){return false;}
    virtual bool isScreen(){return false;}

protected:
    CollitionHandler* collitionHandler = nullptr;
};

#endif //GAME_ENTITY_H
