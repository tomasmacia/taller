//
// Created by Tomás Macía on 14/10/2019.
//

#ifndef GAME_CAMERAPOSITIONCOMPONENT_H
#define GAME_CAMERAPOSITIONCOMPONENT_H

#include <list>
#include "Character.h"

using namespace std;


class Screen {
public:
    Screen(int width, int height, int levelWidth);

    void update();

    void setPlayer(Character* player);
    bool onScreen(int x, int y);
    bool isAtEnd();
    
    void reset(int levelWidth);
    float getLevelPercentageCovered();

    int getWindowWidth(){
        return windowWidth;
    }

    int getWindowHeight(){
        return windowHeight;
    }

    int getMargin(){
        return marginWidth;
    }

    int currentX = 0;

private:

    int windowHeight, windowWidth;
    int marginWidth , offScreenTolerance;
    int currentLevelWidth;
    bool arrivedToEnd = false;

    list<Character*> _players;

    bool shouldMoveCamera();
    bool marginSurpased();
    bool notAtTheEnd();
    bool atTheEnd();
    bool noConnectedPlayerInLeftLimit();
    bool playerIsConnected(Character* player);
    bool inLeftLimit(Character* player);
    bool touchingMargin(Character* player);
    bool surpasedRightLimit(Character* player);
    bool cameraHasReachedLimit();
    bool aPlayerSurpasedRightLimit();

    void scroll();
};


#endif //GAME_CAMERAPOSITIONCOMPONENT_H
