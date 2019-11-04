#include <time.h>
#include <stdlib.h>
#include <iostream>

#include "LevelLimits.h"
#include "CameraComponent.h"

#include <iostream>

LevelLimits::LevelLimits(int windowWidth, int windowHeight, int levelWidth, CameraComponent* camera) {
    initialize(windowWidth,windowHeight,levelWidth,camera);
}

void LevelLimits::initialize(int windowWidth, int windowHeight, int levelWidth, CameraComponent* camera){

    _camera = camera;

    _windowWidth = windowWidth;
    _windowHeight = windowHeight;
    _levelWidth = levelWidth;

    _rangeOfMovementY = windowHeight * 0.2;
    _offsetY = windowHeight * 0.25;

    _toleranceY = _windowHeight * 0.15;
    _toleranceX = _windowWidth * 0.1;

    _minY = _offsetY;
    _maxY = _minY + _rangeOfMovementY + _toleranceY;
    _minX = 0 - _toleranceX;
    _maxX = _windowWidth;
}

void LevelLimits::reset(int windowWidth, int windowHeight, int levelWidth) {
    initialize(windowWidth,windowHeight,levelWidth,_camera);
}

void LevelLimits::update(){
    _minX = _camera->currentX - _toleranceX;
    _maxX = _camera->currentX + _windowWidth;
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

    return (x >= _maxX || x <= _minX) 
            ||
           (y >= _maxY || y <= _minY);
}

bool LevelLimits::newXOutOfRange(int x){
    return (x >= _maxX || x <= _minX);
}

