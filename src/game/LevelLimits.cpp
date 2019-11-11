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

    _characterHeigth = 0;
    _rangeOfMovementY = _windowWidth;

    _maxY = _windowHeight - _characterHeigth;
    _minY = _maxY - _rangeOfMovementY;
    _maxX = _windowWidth;
    _minX = 0;

    _offsetY = _windowHeight - _maxY;

    cout<<"_maxY: "<<_maxY<<endl;
    cout<<"_minY: "<<_minY<<endl;
    cout<<"_maxX: "<<_maxX<<endl;
    cout<<"_minX: "<<_minX<<endl;
}

void LevelLimits::reset(int windowWidth, int windowHeight, int levelWidth) {
    initialize(windowWidth,windowHeight,levelWidth,_camera);
}

void LevelLimits::update(){
    _minX = _camera->currentX;
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

