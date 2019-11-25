//
// Created by axel on 25/11/19.
//

#include "CollitionBox.h"

CollitionBox::CollitionBox(int x, int y, int z, int w, int h, int d, int id, Character* owner) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
    this->h = h;
    this->d = d;
    this->id = id;
    this->owner = owner;
}

bool CollitionBox::intersectsWith(CollitionBox* collitionBox) {
    return hasInsideItsVolumeThePositionPointOf(collitionBox) || collitionBox->hasInsideItsVolumeThePositionPointOf(this);
}

bool CollitionBox::hasInsideItsVolumeThePositionPointOf(CollitionBox* collitionBox){

    return  (x <= collitionBox->x && collitionBox->x <= x + w)
            &&
            (y <= collitionBox->y && collitionBox->y <= y + h)
            &&
            (z <= collitionBox->z && collitionBox->z <= z + d);
}

void CollitionBox::tryPos(int tryX, int tryY, int tryZ) {
    stashedX = x;
    stashedY = y;
    stashedZ = z;
    x = tryX;
    y = tryY;
    z = tryZ;
}

void CollitionBox::resetPos() {
    x = stashedX;
    y = stashedY;
    z = stashedZ;
}
