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

};


#endif //GAME_LEVELBUILDER_H