//
// Created by axel on 12/11/19.
//

#include "NonCharacterLevelLimits.h"

NonCharacterLevelLimits::NonCharacterLevelLimits(int windowWidth, int windowHeight, int levelWidth, CameraComponent* camera){
    LevelLimits();
    initialize(windowWidth,windowHeight,levelWidth,camera);
}

void NonCharacterLevelLimits::initialize(int windowWidth, int windowHeight, int levelWidth, CameraComponent* camera){

    _camera = camera;

    _windowWidth = windowWidth;
    _windowHeight = windowHeight;
    _levelWidth = levelWidth;

    _characterHeigth = _windowHeight * 0.45;
    _rangeOfMovementY = _windowHeight * 0.20;

    _maxY = _windowHeight - _characterHeigth;
    _minY = _maxY - _rangeOfMovementY;
    _maxX = _levelWidth;
    _minX = 0;

    _offsetY = _windowHeight - _rangeOfMovementY - _characterHeigth;
}