//
// Created by axel on 12/11/19.
//

#include "CharacterLevelLimits.h"

CharacterLevelLimits::CharacterLevelLimits(int windowWidth, int windowHeight, int levelWidth, CameraComponent* camera){
    LevelLimits();
    initialize(windowWidth,windowHeight,levelWidth,camera);
}

void CharacterLevelLimits::initialize(int windowWidth, int windowHeight, int levelWidth, CameraComponent* camera){

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

    _offsetY = _windowHeight - _rangeOfMovementY - _characterHeigth;
}

void CharacterLevelLimits::update(){
    _minX = _camera->currentX;
    _maxX = _camera->currentX + _windowWidth - _camera->getMargin() + _offset;
}