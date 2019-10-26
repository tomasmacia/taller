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

    int currentX = 0;

private:
    int _scroll_amount;

    int windowHeight, windowWidth;
    int levelHeight, levelWidth;
    int marginWidth , offScreenTolerance;


    std::list<Entity*> _players;

    bool shouldMoveCamera();
    bool marginSurpased();
    bool notAtTheEnd();
    bool atTheEnd();
    bool noPlayerInLeftLimit();
    bool inLeftLimit(Entity* player);
    bool touchingMargin(Entity* player);

    void scroll();
};


#endif //GAME_CAMERAPOSITIONCOMPONENT_H
