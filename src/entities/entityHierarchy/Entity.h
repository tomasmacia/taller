//
// Created by axel on 27/11/19.
//

#ifndef GAME_ENTITY_H
#define GAME_ENTITY_H


#include "../../net/messaging/Sendable.h"

class Entity {

public:
    virtual void update() = 0;
    virtual Sendable* generateSendable() = 0;

protected:
    int COLLITION_BOX_DEFAULT_DEPTH = 10;
};


#endif //GAME_ENTITY_H
