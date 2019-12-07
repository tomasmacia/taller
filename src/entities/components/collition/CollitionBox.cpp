//
// Created by axel on 25/11/19.
//

#include "CollitionBox.h"
#include "../../entityHierarchy/Entity.h"
#include "../ScreenPosition.h"

CollitionBox::CollitionBox(int centerX, int centerY, int centerZ, int w, int h, int d, int id, bool visual) {

    this->visual = visual;

    this->w = w;
    this->h = h;
    this->d = d;
    this->id = id;

    calculateAndAssignCorners(centerX, centerY, centerZ);
    previousPosition = corners.front();
}

void CollitionBox::calculateAndAssignCorners(int centerX, int centerY, int centerZ) {

    corners.push_back(new Point(centerX - w/2, centerY - h/2, centerZ - d/2));
    corners.push_back(new Point(centerX - w/2, centerY - h/2, centerZ + d/2));
    corners.push_back(new Point(centerX - w/2, centerY + h/2, centerZ - d/2));
    corners.push_back(new Point(centerX - w/2, centerY + h/2, centerZ + d/2));
    corners.push_back(new Point(centerX + w/2, centerY - h/2, centerZ - d/2));
    corners.push_back(new Point(centerX + w/2, centerY - h/2, centerZ + d/2));
    corners.push_back(new Point(centerX + w/2, centerY + h/2, centerZ - d/2));
    corners.push_back(new Point(centerX + w/2, centerY + h/2, centerZ + d/2));
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

void CollitionBox::moveAllCornersBy(int xAmount, int yAmount, int zAmount) {

    for (auto corner : corners){
        corner->moveBy(xAmount,yAmount,zAmount);
    }
}

void CollitionBox::dragToRight(int amount) {
    moveAllCornersBy(amount,0,0);
}

bool CollitionBox::notArrivedAt(Point *destination) {
    return  corners.front()->x != destination->x
            ||
            corners.front()->y != destination->y
            ||
            corners.front()->z != destination->z ;
}

void CollitionBox::moveOneUnitInTheDirectionOf(Point* destination) {

    savePreviousPosition();

    int diffX = destination->x - corners.front()->x;
    int diffY = destination->y - corners.front()->y;
    int diffZ = destination->z - corners.front()->z;

    int norm = (diffX * diffX) + (diffY * diffY) + (diffZ * diffZ);

    if (norm > 0){
        diffX = (int)((diffX * diffX)/norm);
        diffY = (int)((diffY * diffY)/norm);
        diffZ = (int)((diffZ * diffZ)/norm);
    }

    moveAllCornersBy(diffX,diffY,diffZ);
}

CollitionBox::~CollitionBox() {

    for (auto c : corners){
        delete(c);
    }
    corners.clear();
    delete(previousPosition);
}

void CollitionBox::savePreviousPosition() {
    previousPosition->x = corners.front()->x;
    previousPosition->y = corners.front()->y;
    previousPosition->z = corners.front()->z;
}

void CollitionBox::restorePreviousPosition() {

    int diffX = corners.front()->x - previousPosition->x;
    int diffY = corners.front()->y - previousPosition->y;
    int diffZ = corners.front()->z - previousPosition->z;

    moveAllCornersBy(diffX,diffY,diffZ);
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
