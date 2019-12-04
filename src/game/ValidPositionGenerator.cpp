#include <time.h>
#include <stdlib.h>
#include "ValidPositionGenerator.h"

void ValidPositionGenerator::set(int levelWidth, int levelHeight, int levelDepth) {

    _levelWidth = levelWidth;
    _levelHeight = levelHeight;
    _levelDepth = levelDepth;
}

int ValidPositionGenerator::x(){
    srand (std::clock() - start);
    return rand() % _levelWidth;
}

int ValidPositionGenerator::y(){
    return 0;
}

int ValidPositionGenerator::z(){
    srand (std::clock() - start);
    return (rand() % _levelDepth);
}

