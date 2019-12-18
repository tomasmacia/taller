#ifndef GAME_VALIDPOSITIONGENERATOR_H
#define GAME_VALIDPOSITIONGENERATOR_H

#include <cstdio>
#include <ctime>
#include <list>

#include "../entities/components/Point.h"

class ValidPositionGenerator {
public:
    ValidPositionGenerator(int collitionBoxStandartWidth, int collitionBoxStandartHeight, int collitionBoxStandartDepth );
    ~ValidPositionGenerator();

    void set(int levelWidth, int levelHeight, int levelDepth);

    int getX();
    int getY();
    int getZ();

    int endOfLevelX();

    void generateNewPos();

    void generateNewPosAround(int aroundX, int range);

private:
    int generateX();
    int generateY();
    int generateZ();
    bool overlapsWith(Point *pPoint, int x, int y, int z);
    void actuallyGenerateNewPos(int iteration);
    void actuallyGenerateNewPosCenteredWithRange(int center, int range, int iteration);

    int _levelWidth, _levelHeight, _levelDepth;
    int _collitonBoxStandartWidth, _collitonBoxStandartHeight, _collitonBoxStandartDepth;

    std::clock_t start = std::clock();

    std::list<Point*>* generatedPos = nullptr;

    int MAX_RECUSION_DEPTH = 100;
};


#endif //GAME_VALIDPOSITIONGENERATOR_H
