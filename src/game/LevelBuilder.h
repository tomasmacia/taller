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
    Entity& initializeCamera(Entity&);
    void initializePlayers();
    void initializeEnemies();
    void initializeUtilities();
    void initializeWeapons();

    std::vector<float> getParallaxSpeedPerLevel();

    int currentLevel;
    int totalLevels;
};


#endif //GAME_LEVELBUILDER_H