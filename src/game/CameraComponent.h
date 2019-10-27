//
// Created by Tomás Macía on 14/10/2019.
//

#ifndef GAME_CAMERAPOSITIONCOMPONENT_H
#define GAME_CAMERAPOSITIONCOMPONENT_H


#include "ECS.h"

#include <list>
using namespace std;


class CameraComponent : public Component {
public:

    void update() override;
    void init() override;

    void setPlayer(Entity* player);
    bool onScreen(int x, int y);
    
    void reset();

    int getWindowWidth(){return windowWidth;}
    int getWindowHeight(){return windowHeight;}
    float getLevelPercentageCovered();

    int currentX = 0;

private:

    int windowHeight, windowWidth;
    int marginWidth , offScreenTolerance;


    std::list<Entity*> _players;

    bool shouldMoveCamera();
    bool marginSurpased();
    bool notAtTheEnd();
    bool atTheEnd();
    bool noPlayerInLeftLimit();
    bool inLeftLimit(Entity* player);
    bool touchingMargin(Entity* player);
    bool surpasedRightLimit(Entity* player);
    bool cameraHasReachedLimit();
    bool aPlayerSurpasedRightLimit();

    void scroll();
};


#endif //GAME_CAMERAPOSITIONCOMPONENT_H
