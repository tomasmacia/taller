#ifndef GAME_LEVELLIMITS_H
#define GAME_LEVELLIMITS_H

class LevelLimits {
public:
    LevelLimits();

private:
    int windowHeight, windowWidth;
    int levelHeight, levelWidth;
    int marginWidth , offScreenTolerance;
    int minY, maxY, minX, maxX;
    int rangeOfMovement, offset;
};


#endif //GAME_LEVELLIMITS_H
