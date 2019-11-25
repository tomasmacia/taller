//
// Created by Tomás Macía on 14/10/2019.
//
#include "Screen.h"

Screen::Screen(int width, int height, int levelWidth){

    this->currentX = 0;
    this->windowWidth = width;
    this->windowHeight = height;
    this->marginWidth = windowWidth/3;
    this->offScreenTolerance = 2*marginWidth;
    this->currentLevelWidth = levelWidth;
}

void Screen::reset(int levelWidth){
    currentX = 0;
    currentLevelWidth = levelWidth;
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
    this->currentX += (int)(_players.front()->getWalkingSpeed());

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
    return (currentX/currentLevelWidth);
}

bool Screen::onScreen(int x, int y){

    return (x <= (windowWidth + offScreenTolerance) && x >= -offScreenTolerance)
            &&
           (y <= (windowHeight + offScreenTolerance) && y >= -offScreenTolerance); //este luce raro pero es porque el eje y en SDL esta al revez
}

bool Screen::isAtEnd(){
    return arrivedToEnd;
}