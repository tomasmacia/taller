//
// Created by Tomás Macía on 21/09/2019.
//

#ifndef GAME_LEVELBUILDER_H
#define GAME_LEVELBUILDER_H

#include "ECS.h"
#include "TextureWrapper.h"


class LevelBuilder {
public:
    LevelBuilder();

    bool loadNext();
    void initialize();
private:
    void initializeWorld();
    void initializeApropiateParallaxSpeeds(Level currentLevelSprites);
    void initializeCamera();
    void initializePlayers();
    void initializeEnemies();
    void initializeUtilities();
    void initializeWeapons();

    int generateX();
    int generateY();

    std::vector<float> getParallaxSpeedPerLevel();
    Entity* _camera = nullptr;
    TextureWrapper* _texture = nullptr;

    int currentLevel;
    int totalLevels;

    float _overlaySpeed;
    float _floorSpeed;
    float _middleSpeed;
    float _farSpeed;
};


#endif //GAME_LEVELBUILDER_H