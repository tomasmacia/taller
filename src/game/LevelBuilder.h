//
// Created by Tomás Macía on 21/09/2019.
//

#ifndef GAME_LEVELBUILDER_H
#define GAME_LEVELBUILDER_H

#include "../entities/Screen.h"
#include "Controller.h"

class EntityManager;
class Entity;
class LevelBuilder {
public:
    LevelBuilder(Controller* controller, Config* config);
    ~LevelBuilder();


    //API
    //===============================
    void loadNext();
    bool hasNextLevel();
    bool levelFinished();

    //GETTERS
    //===============================
    int getCurrentLevelWidth(){
        return currentLevelWidth;
    }

    EntityManager* getEntityManager(){
        return _entityManager;
    }


    void update();

    int getLevelOn();

private:
    //INITIALIZING
    //===============================
    void initialize();
    void initializeNextLevel();
    void initializeCamera();
    void initializeWorld();
    void initializeLevelDimentions();
    void initializeEnemySpawns();
    void initializePlayers();
    void initializeEnemies();
    void initializeFinalBoss();
    void initializeUtilities();
    void initializeWeapons();
    void resetCamera();
    void resetPlayers();

    //MANAGING OWN STATE
    //===============================
    void prepareForNextLevel();

    //ATRIBUTES
    //===============================
    Screen* _screen = nullptr;
    EntityManager* _entityManager = nullptr;
    Config* _config = nullptr;

    int currentLevel;
    int _levelAmount;

    int currentLevelWidth = 10000; //ONLY USED ON ERROR
    int currentlevelHeight = 300;  //ONLY USED ON ERROR
    int currentlevelDepth = 100;   //ONLY USED ON ERROR

    //un numero entre 0 y 1. 1 significa nada de parallax y 0 es quieto
    float OVERLAY_SPEED_RATIO = 1; //este TIENE que ser 1
    float FLOOR_SPEED_RATIO = 1;   //este TIENE que ser 1
    float MIDDLE_SPEED_RATIO = 0.6;
    float FAR_SPEED_RATIO = 0.4;

    int HORDE_AMOUNT = 5;
    int enemiesPerHorde;
    vector<int> hordeCheckPoints;
    int currentCheckPointNumber;

    void spawnHorde();
};


#endif //GAME_LEVELBUILDER_H