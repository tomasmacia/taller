//
// Created by Tomás Macía on 14/10/2019.
//

#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H


#include <list>
#include <memory>
#include <algorithm>
#include "../entities/entityHierarchy/Entity.h"
#include "../entities/entityHierarchy/PositionalEntity.h"
#include "../entities/Background.h"
#include "../net/messaging/Renderable.h"
#include "../net/messaging/Sendable.h"
#include "../entities/Character.h"

class Manager {
public:
    Manager();
    ~Manager();

    //API
    //===============================
    void update();
    std::list<Sendable*>* generateSendables();
    void prepareForNextLevel();
    void disconectPlayerByID(int id);
    void reconectPlayerByID(int oldID, int newID);

    //ADDING NEW ENTITIES
    //===============================
    void addNPC(PositionalEntity* enemy);
    void addUtilitiy(Entity* utillity);
    void addWeapon(Entity* weapon);
    void addPlayer(PositionalEntity* enemy);
    void addBackLayerBackgrounds(Background* background);
    void addFrontLayerBackgrounds(Background* background);
    void addScreen(Screen* screen);

    //GETTERS
    //===============================
    std::list<Entity*> getPlayers(){
        return players;
    }

private:
    //SORTING
    //===============================
    void sortEntitiesByZ();

    //ADDING NEW ENTITIES
    //===============================
    void destroyAllEntities();
    void destroyNonLevelPersistentEntities();

private:
    //ATRIBUTES
    //===============================
    //no forman una particion (hay overlapings o no estan todas)
    std::list<Entity*> nonLevelPersistentEntities;
    std::list<Character*> players;
    std::list<Entity*> npcs;
    std::list<Entity*> nonMobileEntities;

    //estas listas forman una particion de todas las entities
    // es decir, toda entitie esta en alguna y si esta en una no esta en las otras
    std::list<Entity*> specialEntities;                       //camera and levelLimits
    std::list<PositionalEntity*> entitiesWithPosition;        //only utilities, weapons, npcs and players
    std::list<Background*> backLayerBackgrounds;
    std::list<Background*> fronLayerBackgrounds;

    //for performance
    std::list<Sendable*>* packagesToClients = nullptr;
    Sendable* sendable = nullptr;
};
#endif //GAME_MANAGER_H
