//
// Created by Tomás Macía on 14/10/2019.
//

#ifndef GAME_ENTITYMANAGER_H
#define GAME_ENTITYMANAGER_H


#include <list>
#include <memory>
#include <algorithm>
#include "../entities/entityHierarchy/Entity.h"
#include "../entities/entityHierarchy/PhysicalEntity.h"
#include "../entities/entityHierarchy/Weapon.h"
#include "../entities/Background.h"
#include "../net/messaging/Renderable.h"
#include "../net/messaging/Sendable.h"
#include "../XMLparser/config/config.h"

#include "Controller.h"
#include "../entities/Character.h"
#include "../entities/Enemy.h"
#include "../entities/Knife.h"
#include "../entities/Tube.h"
#include "../entities/Box.h"
#include "../entities/Barrel.h"
#include "../entities/Background.h"

class EntityManager {
public:
    EntityManager(Controller* controller, Config* config);
    ~EntityManager();

    //API
    //===============================
    void update();
    std::list<Sendable*>* generateSendables();
    void prepareForNextLevel();
    void disconectPlayerByID(int id);
    void reconectPlayerByID(int oldID, int newID);

    //ADDING NEW ENTITIES
    //===============================
    Character* addPlayer(int x, int y, int z, int w, int h, int id, int walkingSpeed,);
    void addEnemy(int w, int h, int walkingSpeed);
    void addKnife(int w, int h);
    void addTube(int w, int h);
    void addBox(int w, int h);
    void addBarrel(int w, int h);
    void addBackLayerBackgrounds(Background* background);
    void addFrontLayerBackgrounds(Background* background);
    Screen* addScreen(int screenWidth, int screenHeight, int levelWidth);

    //CREATING ENTITIES
    //===============================
    Character* createCharacter(int x, int y, int z, int w, int h, int id, int walkingSpeed);
    Enemy* createEnemy(int w, int h, int walkingSpeed);
    Knife* createKnife(int w, int h);
    Tube* createTube(int w, int h);
    Box* createBox(int w, int h);
    Barrel* createBarrel(int w, int h);
    Background* createFar();
    Background* createMiddle();
    Background* createFloor();
    Background* createOverlay();

    //GETTERS
    //===============================
    std::list<Character*> getPlayers(){
        return players;
    }

private:
    //SORTING
    //===============================
    void sortEntitiesByZ();

    //DESTROY
    //===============================
    void eraseDeadEntities();
    void untrackDead(Entity* entity);
    void destroyAllEntities();
    void destroyNonLevelPersistentEntities();

    //INIT
    //===============================
    void initializeCollitionManager();

private:
    //ATRIBUTES
    //===============================
    //no forman una particion (hay overlapings o no estan todas)
    std::list<Entity*> nonLevelPersistentEntities;
    std::list<Character*> players;
    std::list<Entity*> enemies;
    std::list<Entity*> inanimatedEntities;

    //estas listas forman una particion de todas las entities
    // es decir, toda entitie esta en alguna y si esta en una no esta en las otras
    std::list<Entity*> specialEntities;                       //camera and levelLimits
    std::list<PhysicalEntity*> physicalEntities;          //only utilities, weapons, enemies and players
    std::list<Background*> backLayerBackgrounds;
    std::list<Background*> fronLayerBackgrounds;

    //for performance
    std::list<Sendable*>* packagesToClients = nullptr;
    Sendable* sendable = nullptr;

    CollitionManager* collitionManager = nullptr;
    Controller* controller = nullptr;
    Config* config = nullptr;
    Screen* screen = nullptr;
};
#endif //GAME_ENTITYMANAGER_H
