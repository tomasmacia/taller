//
// Created by axel on 25/11/19.
//

#include <iostream>
#include "CollitionBox.h"
#include "../../entityHierarchy/Entity.h"
#include "../ScreenPosition.h"

CollitionBox::CollitionBox(int centerX, int centerY, int centerZ, int w, int h, int d, int id, bool visual) {

    this->visual = visual;

    this->w = w;
    this->h = h;
    this->d = d;
    this->id = id;

    center = new Point(centerX,centerY,centerZ);
    calculateAndAssignCorners(center->x, center->y, center->z);
    calculateCandidates();
}

void CollitionBox::calculateAndAssignCorners(int centerX, int centerY, int centerZ) {

    corners.push_back(new Point(center->x - w/2, center->y - h/2, center->z - d/2));
    corners.push_back(new Point(center->x - w/2, center->y - h/2, center->z + d/2));
    corners.push_back(new Point(center->x - w/2, center->y + h/2, center->z - d/2));
    corners.push_back(new Point(center->x - w/2, center->y + h/2, center->z + d/2));
    corners.push_back(new Point(center->x + w/2, center->y - h/2, center->z - d/2));
    corners.push_back(new Point(center->x + w/2, center->y - h/2, center->z + d/2));
    corners.push_back(new Point(center->x + w/2, center->y + h/2, center->z - d/2));
    corners.push_back(new Point(center->x + w/2, center->y + h/2, center->z + d/2));
}

bool CollitionBox::cornerIntersectsWith(CollitionBox* collitionBox, Point* corner) {

    return collitionBox->hasInsideItsVolume(corner);
}

bool CollitionBox::anyCornerIntersectsWith(CollitionBox* collitionBox) {

    for (auto corner : corners){
        if (cornerIntersectsWith(collitionBox,corner)){
            return true;
        }
    }
    return false;
}

bool CollitionBox::hasInsideItsVolume(Point* corner){

    int x = corners.front()->x;
    int y = corners.front()->y;
    int z = corners.front()->z;

    return  (x <= corner->x && corner->x <= x + w)
            &&
            (y <= corner->y && corner->y <= y + h)
            &&
            (z <= corner->z && corner->z <= z + d);
}

void CollitionBox::moveBy(int xAmount, int yAmount, int zAmount) {

    for (auto corner : corners){
        corner->moveBy(xAmount,yAmount,zAmount);
    }
    center->moveBy(xAmount,yAmount,zAmount);
}

void CollitionBox::moveBy(Point delta) {

    for (auto corner : corners){
        corner->moveBy(delta);
    }
    center->moveBy(delta);
}

void CollitionBox::dragToRight(int amount) {
    moveBy(amount, 0, 0);
}

bool CollitionBox::notArrivedAt(Point *destination) {
    return  center->x != destination->x
            ||
            center->y != destination->y
            ||
            center->z != destination->z ;
}

void CollitionBox::moveOneUnitInTheDirectionOf(Point* destination) {

    center->save();

    int minDistance = 100000;
    int distance = 0;
    Point* bestMove = nullptr;

    for (auto* candidateMove : candidateMoves){
        center->plus(*candidateMove);
        distance = center->distanceWith(destination);
        if (distance < minDistance){
            minDistance = distance;
            bestMove = candidateMove;
        }
        center->restore();
    }
    moveBy(*bestMove);
}

CollitionBox::~CollitionBox() {

    for (auto c : corners){
        delete(c);
    }
    corners.clear();
    delete (center);
    for (auto c : candidateMoves){
        delete(c);
    }
    candidateMoves.clear();
}

Entity *CollitionBox::getOwner() {
    return owner;
}

void CollitionBox::setOwner(Entity *owner) {
    this->owner = owner;
}

bool CollitionBox::intersectsWith(CollitionBox *collitionBox) {
    return anyCornerIntersectsWith(collitionBox) || collitionBox->anyCornerIntersectsWith(this);
}

Sendable *CollitionBox::generateSendable() {

    if (screenPosition->onScreen()){

        int x = screenPosition->getX() + (screenPosition->getWidth() - w)/2;
        int y = screenPosition->getY() + (screenPosition->getHeight() - h)/2;;
        return new Sendable(new Renderable("NULL_PATH",Rect(0,0,w,h),Rect(x,y,w,h),false), nullptr);
    }
    else{
        return new Sendable(nullptr, nullptr);
    }
}

void CollitionBox::setScreenPosition(ScreenPosition *screenPosition) {
    this->screenPosition = screenPosition;
}

void CollitionBox::calculateCandidates() {
    candidateMoves.push_back(new Point(-1,0,0));
    candidateMoves.push_back(new Point(0,-1,0));
    candidateMoves.push_back(new Point(0,0,-1));
    candidateMoves.push_back(new Point(0,0,0));
    candidateMoves.push_back(new Point(1,0,0));
    candidateMoves.push_back(new Point(0,1,0));
    candidateMoves.push_back(new Point(0,0,1));
}

void CollitionBox::restorePreviousPosition() {
    moveBy(center->delta().oposite());
}
