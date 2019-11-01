//
// Created by Tomás Macía on 21/09/2019.
//

#ifndef GAME_LEVELBUILDER_H
#define GAME_LEVELBUILDER_H

#include "ECS.h"
#include "TextureWrapper.h"
#include "LevelLimits.h"


class LevelBuilder {
public:
    LevelBuilder();
    ~LevelBuilder();


    //API
    //===============================
    void loadNext();
    bool hasNextLevel();
    bool levelFinished();
    void endLevel();

    //GETTERS
    //===============================
    int getCurrentLevelWidth(){
        return currentLevelWidth;
    }

private:
    //INITIALIZING
    //===============================
    void initialize();
    void initializeNextLevel();
    void initializeCamera();
    void initializeLevelLimits();
    void initializeWorld();
    void initializeLevelWidth(std::string floorSpritePath);
    void initializePlayers();
    void initializeEnemies();
    void initializeUtilities();
    void initializeWeapons();
    void resetCamera();
    void resetLevelLimits();
    void resetPlayers();

    //MANAGING OWN STATE
    //===============================
    void prepareForNextLevel();

    //ATRIBUTES
    //===============================
    Entity* _camera = nullptr;
    Entity* _levelLimits = nullptr;

    int currentLevel;
    int totalLevels;
    bool levelRunning;

    int currentLevelWidth = 10000; //ONLY USED ON ERROR

    //un numero entre 0 y 1. 1 significa nada de parallax y 0 es quieto
    float OVERLAY_SPEED_RATIO = 1; //este TIENE que ser 1
    float FLOOR_SPEED_RATIO = 1;   //este TIENE que ser 1
    float MIDDLE_SPEED_RATIO = 0.6;
    float FAR_SPEED_RATIO = 0.4;
};


#endif //GAME_LEVELBUILDER_H