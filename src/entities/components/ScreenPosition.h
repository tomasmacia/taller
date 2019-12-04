//
// Created by axelmpm on 30/11/19.
//

#ifndef GAME_SCREENPOSITION_H
#define GAME_SCREENPOSITION_H


#include "Position.h"
#include "../Screen.h"

class ScreenPosition {

public:
    ScreenPosition(Position* position, Screen* screen);

    void update();

    int getX();
    int getY();

    bool onScreen();

    Screen* getScreen(){
        return _screen;
    }

private:
    int x;
    int y;

    Position* _spacePosition = nullptr;
    Screen* _screen = nullptr;
};


#endif //GAME_SCREENPOSITION_H
