//
// Created by Tomás Macía on 14/10/2019.
//
#include <string>

#include "Screen.h"
#include "../game/Components/PositionComponent.h"
#include "../game/Components/PhysicsComponent.h"
#include "../game/GameServer.h"
#include "../game/Components/StateComponent.h"

#include <iostream>


void Screen::init(){
    this->currentX = 0;
    this->windowWidth = GameServer::getInstance().getConfig()->screenResolution.width;
    this->windowHeight = GameServer::getInstance().getConfig()->screenResolution.height;
    this->marginWidth = windowWidth/3;
    this->offScreenTolerance = 2*marginWidth;
}

void Screen::reset(){
    currentX = 0;
}


void Screen::update() {
    if (shouldMoveCamera()){
        scroll();
    }

    if (atTheEnd()){
        GameServer::getInstance().endLevel();
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

bool Screen::playerIsConnected(Entity* player) {
    return !player->getComponent<StateComponent>()->isDisconnected();
}

bool Screen::inLeftLimit(Entity* player) {
    return (player->getComponent<PositionComponent>()->getX() <= currentX);
}

bool Screen::atTheEnd() {
    return cameraHasReachedLimit() && aPlayerSurpasedRightLimit();
}

bool Screen::cameraHasReachedLimit(){
    return (currentX + windowWidth) >= GameServer::getInstance().getCurrentLevelWidth();
}

bool Screen::surpasedRightLimit(Entity* player){
    return touchingMargin(player);
}

bool Screen::aPlayerSurpasedRightLimit(){

    for (auto* player : _players){
        if (surpasedRightLimit(player)){return true;}
    }
    return false;
}

bool Screen::notAtTheEnd() {
    return (currentX + windowWidth) < GameServer::getInstance().getCurrentLevelWidth();
}

bool Screen::marginSurpased() {
    for (auto& player : _players){
        if (touchingMargin(player)){return true;}
    }
    return false;
}

bool Screen::touchingMargin(Entity* player) {
    return (player->getComponent<PositionComponent>()->getX() >= (currentX + windowWidth - marginWidth));
}

void Screen::scroll() {
    this->currentX += (int)(_players.front()->getComponent<PhysicsComponent>()->getWalkingSpeed());

    for (auto player: _players){
        if (!playerIsConnected(player) && inLeftLimit(player)){
            player->getComponent<PhysicsComponent>()->drag();
        }
    }
}

void Screen::setPlayer(Entity* player){
    _players.push_back(player); 
}

float Screen::getLevelPercentageCovered(){

    float levelWidth = GameServer::getInstance().getCurrentLevelWidth();
    return (currentX/levelWidth);
}

bool Screen::onScreen(int x, int y){

    return (x <= (windowWidth + offScreenTolerance) && x >= -offScreenTolerance)
            &&
           (y <= (windowHeight + offScreenTolerance) && y >= -offScreenTolerance); //este luce raro pero es porque el eje y en SDL esta al revez
}