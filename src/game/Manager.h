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
    std::list<Entity*> entitiesWithPosition;        //only utilities, weapons, npcs and players
    std::list<Entity*> specialEntities;             //camera and levelLimits
    std::list<Entity*> nonLevelPersistentEntities;
    std::list<Entity*> players;
    std::list<Entity*> backLayerBackgrounds;
    std::list<Entity*> fronLayerBackgrounds;

public:
    void update();
    void render();
    void refresh();

    Entity* addNPC();
    Entity* addUtilitie();
    Entity* addWeapon();
    Entity* addPlayer();
    Entity* addBackLayerBackgrounds();
    Entity* addFrontLayerBackgrounds();
    Entity* addSpecialEntity();
    Entity* addCustomEntity(Entity* e);

    void prepareForNextLevel();
    void destroyAllEntities();
    void destroyNonLevelPersistentEntities();
    std::list<Entity*> getPlayers();
    void sortEntitiesByY();
};
#endif //GAME_MANAGER_H
