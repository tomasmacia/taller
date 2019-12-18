#include <time.h>
#include <stdlib.h>
#include "ValidPositionGenerator.h"

ValidPositionGenerator::ValidPositionGenerator(int collitionBoxStandartWidth, int collitionBoxStandartHeight,
                                               int collitionBoxStandartDepth) {

    _collitonBoxStandartWidth = collitionBoxStandartWidth;
    _collitonBoxStandartHeight = collitionBoxStandartHeight;
    _collitonBoxStandartDepth = collitionBoxStandartDepth;

    generatedPos = new std::list<Point*>();
}

void ValidPositionGenerator::set(int levelWidth, int levelHeight, int levelDepth) {

    _levelWidth = levelWidth;
    _levelHeight = levelHeight;
    _levelDepth = levelDepth;
}

int ValidPositionGenerator::getX(){
    return generatedPos->back()->x;
}

int ValidPositionGenerator::getY(){
    return generatedPos->back()->y;
}

int ValidPositionGenerator::getZ(){
    return generatedPos->back()->z;
}

int ValidPositionGenerator::endOfLevelX() {
    return _levelWidth;
}

void ValidPositionGenerator::actuallyGenerateNewPos(int iteration) {

    if (iteration <= MAX_RECUSION_DEPTH){

        int x = generateX();
        int y = generateY();
        int z = generateZ();

        for (auto prevPos : *generatedPos){
            if (overlapsWith(prevPos,x,y,z)){
                actuallyGenerateNewPos(iteration + 1);
                break;
            }
        }
        generatedPos->push_back(new Point(x,y,z));
    }
}

void ValidPositionGenerator::actuallyGenerateNewPosCenteredWithRange(int center, int range, int iteration) {

    if (iteration <= MAX_RECUSION_DEPTH){

        srand (std::clock() - start);

        int coinFlip = rand()%3 - 1;
        if (coinFlip == 0){coinFlip = 1;}

        int x = center + range * coinFlip;
        int y = generateY();
        int z = generateZ();

        for (auto prevPos : *generatedPos){
            if (overlapsWith(prevPos,x,y,z)){
                actuallyGenerateNewPosCenteredWithRange(center,range,iteration + 1);
                break;
            }
        }
        generatedPos->push_back(new Point(x,y,z));
    }
}

void ValidPositionGenerator::generateNewPos() {
    actuallyGenerateNewPos(0); //recursive
}

int ValidPositionGenerator::generateX() {
    srand (std::clock() - start);
    return rand() % (_levelWidth - _collitonBoxStandartWidth - 1);
}

int ValidPositionGenerator::generateY() {
    return 0;
}

int ValidPositionGenerator::generateZ() {
    srand (std::clock() - start);
    return rand() % (_levelDepth - _collitonBoxStandartDepth - 1 );
}

bool ValidPositionGenerator::overlapsWith(Point *pPoint, int x, int y, int z) {

    int minX = pPoint->x - _collitonBoxStandartWidth/2;
    int maxX = pPoint->x + _collitonBoxStandartWidth/2;
    int minY = pPoint->y - _collitonBoxStandartHeight/2;
    int maxY = pPoint->y + _collitonBoxStandartHeight/2;
    int minZ = pPoint->z - _collitonBoxStandartDepth/2;
    int maxZ = pPoint->z + _collitonBoxStandartDepth/2;

    return minX <= x && x <= maxX   &&
           minY <= y && y <= maxY   &&
           minZ <= z && z <= maxZ;
}

void ValidPositionGenerator::generateNewPosAround(int aroundX, int range) {
    actuallyGenerateNewPosCenteredWithRange(aroundX,range,0);
}

ValidPositionGenerator::~ValidPositionGenerator() {
    for (auto pos : *generatedPos){
        delete(pos);
    }
    delete(generatedPos);
}

