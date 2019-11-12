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

    _characterHeigth = _windowHeight * 0.45;
    _offset = _windowWidth / 50;
    _rangeOfMovementY = _windowHeight * 0.20;

    _maxY = _windowHeight - _characterHeigth;
    _minY = _maxY - _rangeOfMovementY;
    _maxX = _windowWidth - _camera->getMargin() + _offset;
    _minX = 0;

    _offsetY = _windowHeight - _maxY;
}

void LevelLimits::reset(int windowWidth, int windowHeight, int levelWidth) {
    initialize(windowWidth,windowHeight,levelWidth,_camera);
}

void LevelLimits::update(){
    _minX = _camera->currentX;
    _maxX = _camera->currentX + _windowWidth - _camera->getMargin() + _offset;
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

