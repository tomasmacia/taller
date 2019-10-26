#include <time.h>
#include <stdlib.h>

#include "LevelLimits.h"

#include <iostream>

LevelLimits::LevelLimits(int windowWidth, int windowHeight, int levelWidth) {

    srand (time(NULL));

    _windowWidth = windowWidth;
    _windowHeight = windowHeight;
    _levelWidth = levelWidth;

    _rangeOfMovementY = windowHeight * 0.2;
    _offsetY = windowHeight * 0.3;

    _minY = _offsetY;
    _maxY = _minY + _rangeOfMovementY;
    _minX = 0;
    _maxX = _windowWidth;
}

void LevelLimits::update(){
    
}

int LevelLimits::generateValidInScreenX(){
    //return rand() % _levelWidth;
    return rand() % _windowWidth;
}

int LevelLimits::generateValidInScreenY(){
    return (rand() % _rangeOfMovementY) + _offsetY;
}

bool LevelLimits::newPositionOutOfRange(int x, int y){

    return (x >= _maxX || x <= _minX) 
            ||
           (y >= _maxY || y <= _minY);
}

