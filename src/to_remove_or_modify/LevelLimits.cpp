#include <time.h>
#include <stdlib.h>
#include <iostream>

#include "LevelLimits.h"
#include "CameraComponent.h"

#include <iostream>

void LevelLimits::reset(int windowWidth, int windowHeight, int levelWidth) {
    initialize(windowWidth,windowHeight,levelWidth,_camera);
}

int LevelLimits::generateValidInScreenX(){
    srand (std::clock() - start);
    return rand() % _levelWidth;
}

int LevelLimits::generateValidInScreenY(){
    srand (std::clock() - start);
    return (rand() % _rangeOfMovementY) + _offsetY;
}

bool LevelLimits::newPositionOutOfRange(int x, int y){
    return (x > _maxX || x < _minX)
            ||
           (y > _maxY || y < _minY);
}

bool LevelLimits::newXOutOfRange(int x){
    return (x >= _maxX || x <= _minX);
}
