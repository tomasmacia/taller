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
public:
    Manager();
    ~Manager();

    //API
    //===============================
    void update();
    std::list<ToClientPack*>* generateRenderables();
    void prepareForNextLevel();
    void disconectPlayerByID(int id);
    void reconectPlayerByID(int id);

    //ADDING NEW ENTITIES
    //===============================
    Entity* addNPC();
    Entity* addUtilitie();
    Entity* addWeapon();
    Entity* addPlayer();
    Entity* addBackLayerBackgrounds();
    Entity* addFrontLayerBackgrounds();
    Entity* addSpecialEntity();

    //GETTERS
    //===============================
    std::list<Entity*> getPlayers(){
        return players;
    }

private:
    //SORTING
    //===============================
    void sortEntitiesByY();

    //ADDING NEW ENTITIES
    //===============================
    void destroyAllEntities();
    void destroyNonLevelPersistentEntities();

private:
    //ATRIBUTES
    //===============================
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

    //for performance
    std::list<ToClientPack*>* packagesToClients = nullptr;
    ToClientPack* renderable = nullptr;
};
#endif //GAME_MANAGER_H
