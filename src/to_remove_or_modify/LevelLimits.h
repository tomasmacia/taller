#ifndef GAME_LEVELLIMITS_H
#define GAME_LEVELLIMITS_H

#include <cstdio>
#include <ctime>

#include "../entities/Screen.h"


class LevelLimits : public Component{
public:
    LevelLimits(){}

    void reset(int windowWidth, int windowHeight, int levelWidth);

    int generateValidInScreenX();
    int generateValidInScreenY();
    bool newPositionOutOfRange(int x, int y);
    bool newXOutOfRange(int newX);

protected:
    virtual void initialize(int windowWidth, int windowHeight, int levelWidth, Screen* camera){}

    int _windowHeight, _windowWidth, _levelWidth;

    int _minY, _maxY, _minX, _maxX;
    int _rangeOfMovementY, _offsetY, _characterHeigth,_offset;

    std::clock_t start = std::clock();

    Screen* _camera = nullptr;
};


#endif //GAME_LEVELLIMITS_H
