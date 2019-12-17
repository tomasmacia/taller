//
// Created by Tomás Macía on 14/10/2019.
//

#ifndef GAME_ENTITYMANAGER_H
#define GAME_ENTITYMANAGER_H

#include <list>

#include "ValidPositionGenerator.h"

#include "../net/messaging/Renderable.h"

#include "../net/messaging/Sendable.h"
#include "../XMLparser/config/config.h"

#include "../logger/LogManager.h"

#include "../entities/entityHierarchy/PhysicalEntity.h"
#include "../entities/Background.h"
#include "../entities/Character.h"
#include "../entities/Enemy.h"
#include "../entities/Knife.h"
#include "../entities/Tube.h"
#include "../entities/Box.h"
#include "../entities/Barrel.h"
#include "../entities/Background.h"
#include "../entities/Life.h"
#include "../entities/Score.h"
#include "../entities/FinalBoss.h"


class GameServer;
class Controller;
class EntityManager {
public:
    EntityManager(Controller *controller, Config *config);
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
    Character* addPlayer(int x, int y, int z,int id);
    void addEnemy();
    void addFinalBoss();
    void addKnife();
    void addTube();
    void addBox();
    void addBarrel();
    void addFar(const string& spritePath, float parallaxSpeed);
    void addMiddle(const string& spritePath, float parallaxSpeed);
    void addFloor(const string& spritePath, float parallaxSpeed);
    void addOverlay(const string& spritePath, float parallaxSpeed);

    Screen* addScreen(int screenWidth, int screenHeight, int levelWidth, int levelDepth);
    //CREATING ENTITIES
    //===============================
    Character* createCharacter(int x, int y, int z, int id);
    Enemy* createEnemy();
    FinalBoss *createFinalBoss();
    Knife* createKnife();
    Tube* createTube();
    Box* createBox();
    Barrel* createBarrel();
    Background* createFar(const string& spritePath, float parallaxSpeed);
    Background* createMiddle(const string& spritePath, float parallaxSpeed);
    Background* createFloor(const string& spritePath, float parallaxSpeed);
    Background* createOverlay(const string& spritePath, float parallaxSpeed);

    void setLevelParameters( int levelWidth, int levelHeight, int levelDepth);

    //GETTERS
    //===============================
    std::list<Character*> getPlayers(){
        return players;
    }

    bool bossKilled();

    void setGame(GameServer *gameServer);

private:
    //SORTING
    //===============================
    void sortEntitiesByZ();

    //DESTROY
    //===============================
    void eraseDeadEntities();
    void untrackDead(PhysicalEntity* entity);
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
    std::list<Enemy*> enemies;
    std::list<UnanimatedEntity*> unanimatedEntities;

    //estas listas forman una particion de todas las entities
    // es decir, toda entity esta en alguna getY si esta en una no esta en las otras
    std::list<Entity*> specialEntities;                       //camera and levelLimits
    std::list<PhysicalEntity*> physicalEntities;          //only utilities, weapons, enemies and players
    std::list<Background*> backLayerBackgrounds;
    std::list<Background*> frontLayerBackgrounds;
    FinalBoss* finalBoss = nullptr;

    ValidPositionGenerator* validPositionGenerator = nullptr;

    //for performance
    std::list<Sendable*>* packagesToClients = nullptr;

    GameServer *gameServer = nullptr;
    CollitionManager* collitionManager = nullptr;
    Controller* controller = nullptr;
    Config* config = nullptr;
    Screen* screen = nullptr;

    //Parametros de construccion de entidades
    float CHARACTER_WIDTH_SCALE = 0.3;
    float CHARACTER_HEIGHT_SCALE = 0.5;
    float ENEMY_WIDTH_SCALE = 0.2;
    float ENEMY_HEIGHT_SCALE = 0.5;
    float BOSS_WIDTH_SCALE = 0.3;
    float BOSS_HEIGHT_SCALE = 0.5;
    float UTILITY_WIDTH_SCALE = 0.2;
    float UTILITY_HEIGHT_SCALE = 0.5;
    float WEAPON_WIDTH_SCALE = 0.2;
    float WEAPON_HEIGHT_SCALE = 0.5;
    float WAKING_SPEED_FACTOR = 0.01;
    float JUMPING_SPEED_FACTOR = 0.03;

    bool VISUAL_COLLITION_BOX = false;
    int NON_TRACKABLE_COLLITION_BOX_ID = -1;
    int DEFAULT_COLLITION_BOX_WIDTH = 5;
    int DEFAULT_COLLITION_BOX_HEIGHT = 5;
    int DEFAULT_COLLITION_BOX_DEPTH = 20;

    float PICK_COLLITON_BOX_SCALE_FACTOR = 2;
    float ATTACK_COLLITON_BOX_SCALE_FACTOR = 1.1;
    float NORMAL_COLLITON_BOX_SCALE_FACTOR_WIDTH = 0.5;
    float NORMAL_COLLITON_BOX_SCALE_FACTOR_HEIGHT = 1;

    bool bossIsDead = false;

    void correctlyRemovePlayer(Character *character);
};
#endif //GAME_ENTITYMANAGER_H
