//
// Created by Tomás Macía on 14/10/2019.
//

#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H


#include <list>
#include <memory>
#include <algorithm>

#include "ECS.h"

class Manager {
private:
    std::list<Entity*> entities;
    std::list<Entity*> nonLevelPersistentEntities;
    std::list<Entity*> players;
    std::list<Entity*> backgrounds;

public:
    void update();
    void render();
    void refresh();
    Entity* addEntity();
    Entity* addNonPersistentEntity();
    Entity* addPlayer();
    Entity* addBackground();
    Entity* addCustomEntity(Entity* e);
    void destroyAllEntities();
    void destroyNonLevelPersistentEntities();
    std::list<Entity*> getPlayers();
};
#endif //GAME_MANAGER_H
