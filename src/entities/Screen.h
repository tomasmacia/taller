//
// Created by Tomás Macía on 14/10/2019.
//

#ifndef GAME_CAMERAPOSITIONCOMPONENT_H
#define GAME_CAMERAPOSITIONCOMPONENT_H

#include <list>
#include "../entities/entityHierarchy/Entity.h"

using namespace std;

class Character;
class Screen : public Entity{
public:
    Screen(int width, int height, int levelWidth, int levelDepth,
           CollitionManager *collitionManager);

    void update() override ;
    list<Sendable*> generateSendable() override ;

    void setPlayer(Character* player);
    bool onScreen(int x, int y);
    bool isAtEnd();
    
    void reset(int levelWidth);
    float getLevelPercentageCovered();

    void setLevelWidth(int levelWidth){
        currentLevelWidth = levelWidth;
    }

    int getLevelDepth(){
        return levelDepth;
    }

    int getWindowWidth(){
        return windowWidth;
    }

    int getWindowHeight(){
        return windowHeight;
    }

    int getMargin(){
        return marginWidth;
    }

    int getLevelWidth(){
        return currentLevelWidth;
    }

    int currentX = 0;

    bool isScreen() override {
        return true;
    }

    void removePlayer(int id);

private:
    int windowHeight, windowWidth, levelDepth;
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
