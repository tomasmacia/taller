#ifndef GAME_VALIDPOSITIONGENERATOR_H
#define GAME_VALIDPOSITIONGENERATOR_H

#include <cstdio>
#include <ctime>

class ValidPositionGenerator {
public:
    void set(int levelWidth, int levelHeight, int levelDepth);

    int x();
    int y();
    int z();

private:
    int _levelWidth, _levelHeight, _levelDepth;
    std::clock_t start = std::clock();
};


#endif //GAME_VALIDPOSITIONGENERATOR_H
