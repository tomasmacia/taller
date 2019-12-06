//
// Created by axelmpm on 5/12/19.
//

#ifndef GAME_SCENEDIRECTOR_H
#define GAME_SCENEDIRECTOR_H


#include "../net/messaging/Sendable.h"
#include "EntityManager.h"

class SceneDirector {

public:
    SceneDirector(EntityManager* entityManager);

    Sendable* generateSendables();

private:
    EntityManager* entityManager = nullptr;
};


#endif //GAME_SCENEDIRECTOR_H
