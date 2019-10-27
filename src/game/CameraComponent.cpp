//
// Created by Tomás Macía on 14/10/2019.
//
#include <string>

#include "CameraComponent.h"
#include "PositionComponent.h"
#include "PhysicsComponent.h"
#include "Game.h"

#include <iostream>


void CameraComponent::init(){
    this->currentX = 0;
    this->windowWidth = Game::getInstance().getConfig()->screenResolution.width;
    this->windowHeight = Game::getInstance().getConfig()->screenResolution.height;
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
        Game::getInstance().endLevel();
    }
}

bool CameraComponent::shouldMoveCamera() {
    return (noPlayerInLeftLimit() && marginSurpased() && notAtTheEnd());
}

bool CameraComponent::noPlayerInLeftLimit() {
    for (auto* player : _players){
        if (inLeftLimit(player)){return false;}
    }
    return true;
}

bool CameraComponent::inLeftLimit(Entity* player) {
    return (player->getComponent<PositionComponent>()->getX() <= currentX);
}

bool CameraComponent::atTheEnd() {
    return cameraHasReachedLimit() && aPlayerSurpasedRightLimit();
}

bool CameraComponent::cameraHasReachedLimit(){
    return (currentX + windowWidth) >= Game::getInstance().getCurrentLevelWidth();
}

bool CameraComponent::surpasedRightLimit(Entity* player){
    return (currentX + windowWidth - offScreenTolerance/30) < player->getComponent<PositionComponent>()->getX();
}

bool CameraComponent::aPlayerSurpasedRightLimit(){

    for (auto* player : _players){
        if (surpasedRightLimit(player)){return true;}
    }
    return false;
}

bool CameraComponent::notAtTheEnd() {
    return (currentX + windowWidth) < Game::getInstance().getCurrentLevelWidth();
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
}

void CameraComponent::setPlayer(Entity* player){
    _players.push_back(player); 
}

int CameraComponent::getSpeed(){
    return (int)(_players.front()->getComponent<PhysicsComponent>()->getWalkingSpeed());
}

bool CameraComponent::onScreen(int x, int y){

    return (x <= (windowWidth + offScreenTolerance) && x >= -offScreenTolerance)
            &&
           (y <= (windowHeight + offScreenTolerance) && y >= -offScreenTolerance); //este luce raro pero es porque el eje y en SDL esta al revez
}