//
// Created by axelmpm on 2/12/19.
//

#include "Point.h"

Point::Point(int x, int y, int z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

void Point::moveBy(int xAmount, int yAmount, int zAmount) {
    x += xAmount;
    y += yAmount;
    z += zAmount;
}
