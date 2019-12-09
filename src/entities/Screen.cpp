//
// Created by Tomás Macía on 14/10/2019.
//
#include "Screen.h"
#include "components/collition/ScreenCollitionHandler.h"
#include "Character.h"


Screen::Screen(int width, int height, int levelWidth, int levelDepth, CollitionManager* collitionManager){


    this->currentX = 0;
    this->windowWidth = width;
    this->windowHeight = height;
    this->marginWidth = windowWidth/3;
    this->offScreenTolerance = 2*marginWidth;
    this->currentLevelWidth = levelWidth;
    this->levelDepth = levelDepth;

    this->collitionHandler = new ScreenCollitionHandler(collitionManager, this, false);
    this->collitionHandler->setOwnerToAllCollitionBox(this);
}

void Screen::reset(int levelWidth){
    ScreenCollitionHandler* screenCollitionHandler = (ScreenCollitionHandler*) collitionHandler;

    currentX = 0;
    currentLevelWidth = levelWidth;
    arrivedToEnd = false;
    screenCollitionHandler->resetAll(this);
}

void Screen::update() {

    if (shouldMoveCamera()){
        scroll();
    }

    if (atTheEnd()){
        arrivedToEnd = true;
    }
}

bool Screen::shouldMoveCamera() {
    return (noConnectedPlayerInLeftLimit() && marginSurpased() && notAtTheEnd());
}

bool Screen::noConnectedPlayerInLeftLimit() {
    for (auto* player : _players){

        if (playerIsConnected(player)){
            if (inLeftLimit(player) ){
                return false;
            }
        }
    }
    return true;
}

bool Screen::playerIsConnected(Character* player) {
    return !player->isDisconnected();
}

bool Screen::inLeftLimit(Character* player) {
    return (player->getX() <= currentX);
}

bool Screen::atTheEnd() {
    return cameraHasReachedLimit() && aPlayerSurpasedRightLimit();
}

bool Screen::cameraHasReachedLimit(){
    return (currentX + windowWidth) >= currentLevelWidth;
}

bool Screen::surpasedRightLimit(Character* player){
    return touchingMargin(player);
}

bool Screen::aPlayerSurpasedRightLimit(){

    for (auto* player : _players){
        if (surpasedRightLimit(player)){return true;}
    }
    return false;
}

bool Screen::notAtTheEnd() {
    return (currentX + windowWidth) < currentLevelWidth;
}

bool Screen::marginSurpased() {
    for (auto& player : _players){
        if (touchingMargin(player)){return true;}
    }
    return false;
}

bool Screen::touchingMargin(Character* player) {
    return (player->getX() >= (currentX + windowWidth - marginWidth));
}

void Screen::scroll() {
    int amount = (int)(_players.front()->getWalkingSpeed());
    this->currentX += amount;
    this->collitionHandler->dragToRight(amount);

    for (auto player: _players){
        if (!playerIsConnected(player) && inLeftLimit(player)){
            player->drag();
        }
    }
}

void Screen::setPlayer(Character* player){
    _players.push_back(player); 
}

float Screen::getLevelPercentageCovered(){
    float percentage = (float)currentX/(float)currentLevelWidth;
    return percentage;
}

bool Screen::onScreen(int x, int y){

    return (x <= (windowWidth + offScreenTolerance) && x >= -offScreenTolerance)
            &&
           (y <= (windowHeight + offScreenTolerance) && y >= -offScreenTolerance); //este luce raro pero es porque el eje y en SDL esta al revez
}

bool Screen::isAtEnd(){
    return arrivedToEnd;
}

list<Sendable*> Screen::generateSendable() {
    return collitionHandler->generateSendable();
}
