//
// Created by Tomás Macía on 21/09/2019.
//

#ifndef GAME_LEVELBUILDER_H
#define GAME_LEVELBUILDER_H

#include "ECS.h"


class LevelBuilder {
public:
    LevelBuilder();

    bool loadNext();
    void initialize();
private:
    void initializeWorld();
    void initializeCamera();
    void initializePlayers();
    void initializeEnemies();
    void initializeUtilities();
    void initializeWeapons();

    int generateX();
    int generateY();

    std::vector<float> getParallaxSpeedPerLevel();
    Entity* _camera = nullptr;

    int currentLevel;
    int totalLevels;

    int OVERLAY_SPEED = 3;
    int FLOOR_SPEED = 3;
    int MIDDLE_SPEED = 2;
    int FAR_SPEED = 1;
};


#endif //GAME_LEVELBUILDER_H