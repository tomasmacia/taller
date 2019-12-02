//
// Created by axel on 25/11/19.
//

#include "CollitionBox.h"

CollitionBox::CollitionBox(int x, int y, int z, int w, int h, int d, int id) {

    if (w == -1){
        w = DEFAULT_WIDTH;
    }
    if (h == -1){
        h = DEFAULT_HEIGHT;
    }
    if (d == -1){
        d = DEFAULT_DEPTH;
    }
    if (id < 0){
        id = DEFAULT_NULL_ID;
    }

    this->w = w;
    this->h = h;
    this->d = d;
    this->id = id;

    calculateAndAssignCorners(x,y,z);
    previousPosition = new Point(x,y,z);
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

bool CollitionBox::intersectsWith(CollitionBox* collitionBox) {

    return anyCornerIntersectsWith(collitionBox);
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

void CollitionBox::calculateAndAssignCorners(int x, int y, int z) {

    corners.push_back(new Point(x + 0,y + 0,z + 0));
    corners.push_back(new Point(x + 0,y + 0,z + d));
    corners.push_back(new Point(x + 0,y + h,z + 0));
    corners.push_back(new Point(x + 0,y + h,z + d));
    corners.push_back(new Point(x + w,y + 0,z + 0));
    corners.push_back(new Point(x + w,y + 0,z + d));
    corners.push_back(new Point(x + w,y + h,z + 0));
    corners.push_back(new Point(x + w,y + h,z + d));
}

void CollitionBox::setOwner(Entity *owner) {
    this->owner = owner;
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

    diffX = (int)((diffX * diffX)/norm);
    diffY = (int)((diffY * diffY)/norm);
    diffZ = (int)((diffZ * diffZ)/norm);

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
