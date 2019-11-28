//
// Created by Tomás Macía on 21/09/2019.
//

#ifndef GAME_LEVELBUILDER_H
#define GAME_LEVELBUILDER_H

#include "../game/Manager.h"
#include "../entities/Screen.h"

class Entity;
class LevelBuilder {
public:
    LevelBuilder(Manager* manager, Config* config);
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

private:
    //INITIALIZING
    //===============================
    void initialize();
    void initializeNextLevel();
    void initializeCollitionManager();
    void initializeCamera();
    void initializeWorld();
    void initializeLevelWidth(std::string floorSpritePath);
    void initializePlayers();
    void initializeEnemies();
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
    CollitionManager* _collitionManager = nullptr;

    Manager* _manager = nullptr;
    Config* _config = nullptr;

    int currentLevel;
    int _levelAmount;

    int currentLevelWidth = 10000; //ONLY USED ON ERROR

    //un numero entre 0 y 1. 1 significa nada de parallax y 0 es quieto
    float OVERLAY_SPEED_RATIO = 1; //este TIENE que ser 1
    float FLOOR_SPEED_RATIO = 1;   //este TIENE que ser 1
    float MIDDLE_SPEED_RATIO = 0.6;
    float FAR_SPEED_RATIO = 0.4;
};


#endif //GAME_LEVELBUILDER_H