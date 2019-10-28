//
// Created by Tomás Macía on 14/10/2019.
//

#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H


#include <list>
#include <memory>
#include <algorithm>

#include "ToClientPack.h"

#include "ECS.h"

class Manager {
private:
    //no forman una particion (hay overlapings o no estan todas)
    std::list<Entity*> nonLevelPersistentEntities;
    std::list<Entity*> players;
    std::list<Entity*> npcs;
    std::list<Entity*> nonMobileEntities;

    //estas listas forman una particion de todas las entities
    // es decir, toda entitie esta en alguna y si esta en una no esta en las otras
    std::list<Entity*> specialEntities;             //camera and levelLimits
    std::list<Entity*> entitiesWithPosition;        //only utilities, weapons, npcs and players
    std::list<Entity*> backLayerBackgrounds;
    std::list<Entity*> fronLayerBackgrounds;

public:
    void update();
    std::list<ToClientPack> generateRenderables();
    //void render();
    //void refresh();

    ~Manager();
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
