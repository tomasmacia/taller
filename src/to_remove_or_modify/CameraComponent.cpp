//
// Created by Tomás Macía on 14/10/2019.
//
#include <string>

#include "CameraComponent.h"
#include "../game/Components/PositionComponent.h"
#include "../game/Components/PhysicsComponent.h"
#include "../game/GameServer.h"
#include "../game/Components/StateComponent.h"

#include <iostream>


void CameraComponent::init(){
    this->currentX = 0;
    this->windowWidth = GameServer::getInstance().getConfig()->screenResolution.width;
    this->windowHeight = GameServer::getInstance().getConfig()->screenResolution.height;
    this->marginWidth = windowWidth/3;
    this->offScreenTolerance = 2*marginWidth;
}

void CameraComponent::reset(){
    currentX = 0;
}


void CameraComponent::update() {
    if (shouldMoveCamera()){
        scroll();
    }

    if (atTheEnd()){
        GameServer::getInstance().endLevel();
    }
}

bool CameraComponent::shouldMoveCamera() {
    return (noConnectedPlayerInLeftLimit() && marginSurpased() && notAtTheEnd());
}

bool CameraComponent::noConnectedPlayerInLeftLimit() {
    for (auto* player : _players){

        if (playerIsConnected(player)){
            if (inLeftLimit(player) ){
                return false;
            }
        }
    }
    return true;
}

bool CameraComponent::playerIsConnected(Entity* player) {
    return !player->getComponent<StateComponent>()->isDisconnected();
}

bool CameraComponent::inLeftLimit(Entity* player) {
    return (player->getComponent<PositionComponent>()->getX() <= currentX);
}

bool CameraComponent::atTheEnd() {
    return cameraHasReachedLimit() && aPlayerSurpasedRightLimit();
}

bool CameraComponent::cameraHasReachedLimit(){
    return (currentX + windowWidth) >= GameServer::getInstance().getCurrentLevelWidth();
}

bool CameraComponent::surpasedRightLimit(Entity* player){
    return touchingMargin(player);
}

bool CameraComponent::aPlayerSurpasedRightLimit(){

    for (auto* player : _players){
        if (surpasedRightLimit(player)){return true;}
    }
    return false;
}

bool CameraComponent::notAtTheEnd() {
    return (currentX + windowWidth) < GameServer::getInstance().getCurrentLevelWidth();
}

bool CameraComponent::marginSurpased() {
    for (auto& player : _players){
        if (touchingMargin(player)){return true;}
    }
    return false;
}

bool CameraComponent::touchingMargin(Entity* player) {
    return (player->getComponent<PositionComponent>()->getX() >= (currentX + windowWidth - marginWidth));
}

void CameraComponent::scroll() {
    this->currentX += (int)(_players.front()->getComponent<PhysicsComponent>()->getWalkingSpeed());

    for (auto player: _players){
        if (!playerIsConnected(player) && inLeftLimit(player)){
            player->getComponent<PhysicsComponent>()->drag();
        }
    }
}

void CameraComponent::setPlayer(Entity* player){
    _players.push_back(player); 
}

float CameraComponent::getLevelPercentageCovered(){

    float levelWidth = GameServer::getInstance().getCurrentLevelWidth();
    return (currentX/levelWidth);
}

bool CameraComponent::onScreen(int x, int y){

    return (x <= (windowWidth + offScreenTolerance) && x >= -offScreenTolerance)
            &&
           (y <= (windowHeight + offScreenTolerance) && y >= -offScreenTolerance); //este luce raro pero es porque el eje y en SDL esta al revez
}