//
// Created by Tomás Macía on 21/09/2019.
//

#ifndef GAME_LEVELBUILDER_H
#define GAME_LEVELBUILDER_H


class LevelBuilder {
public:
    LevelBuilder();

    bool loadNext();
    void initialize();
private:
    void initializeWorld();
    void initializePlayers();
    void initializeEnemies();
    void initializeUtilities();
    void initializeWeapons();

    int currentLevel;
    int totalLevels;
};


#endif //GAME_LEVELBUILDER_H
