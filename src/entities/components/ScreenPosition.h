//
// Created by axelmpm on 30/11/19.
//

#ifndef GAME_SCREENPOSITION_H
#define GAME_SCREENPOSITION_H


#include "Position.h"
#include "../Screen.h"

class ScreenPosition {

public:
    ScreenPosition(int width, int height, int depth, Position* position, Screen* screen);

    void update();

    int getX();
    int getY();

    bool onScreen();

    Screen* getScreen(){
        return _screen;
    }

    int getWidth();

    int getHeight();

    int getXWithPos(Point *point);
    int getYWithPos(Point *point);

private:
    int x;
    int y;
    int width;
    int height;

    Position* _spacePosition = nullptr;
    Screen* _screen = nullptr;
};


#endif //GAME_SCREENPOSITION_H
