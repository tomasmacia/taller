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

    void loadNext();
    bool hasNextLevel();

    int getCurrentLevelWidth();

private:
    void initialize();
    void initializeNextLevel();
    void initializeCamera();
    void initializeLevelLimits();
    void initializeWorld();
    void initializeApropiateParallaxSpeeds(Level currentLevelSprites);
    void initializePlayers();
    void initializeEnemies();
    void initializeUtilities();
    void initializeWeapons();

    void resetCamera();
    void resetLevelLimits();
    void resetPlayers();
    void destroyUselessEntities();

    int generateX();
    int generateY();

    std::vector<float> getParallaxSpeedPerLevel();
    Entity* _camera = nullptr;
    TextureWrapper* _texture = nullptr;
    Entity* _levelLimits = nullptr;

    int currentLevel;
    int totalLevels;

    int currentLevelWidth;

    float _overlaySpeedRatio;
    float _floorSpeedRatio;
    float _middleSpeedRatio;
    float _farSpeedRatio;
};


#endif //GAME_LEVELBUILDER_H