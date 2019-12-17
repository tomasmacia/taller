//
// Created by axelmpm on 2/12/19.
//

#include "Point.h"

Point::Point(int x, int y, int z) {
    this->x = x;
    this->y = y;
    this->z = z;
    savedX = x + 1;
    savedY = y + 1;
    savedZ = z + 1;
}

void Point::moveBy(int xAmount, int yAmount, int zAmount) {
    x += xAmount;
    y += yAmount;
    z += zAmount;
}

void Point::moveBy(Point delta) {
    plus(delta);
}

void Point::plus(Point delta) {
    x += delta.x;
    y += delta.y;
    z += delta.z;

}

int Point::distanceWith(Point *other) {

    int diffX = x - other->x;
    int diffY = y - other->y;
    int diffZ = z - other->z;

    return diffX*diffX + diffY*diffY + diffZ*diffZ;
}

void Point::save() {
    savedX = x;
    savedY = y;
    savedZ = z;
}

void Point::restore() {
    x = savedX;
    y = savedY;
    z = savedZ;
}

Point Point::delta() {
    return Point(x - savedX, y - savedY, z - savedZ);
}

Point Point::minus(Point* other) {
    return Point(x - other->x, y - other->y, z - other->z);
}

Point Point::oposite() {
    return Point(-x,-y,-z);
}

bool Point::isZero() {
    return x == 0 && y == 0 && z == 0;
}

void Point::setAt(Point *pPoint) {
    x = pPoint->x;
    y = pPoint->y;
    z = pPoint->z;
}

bool Point::coincidesWith(Point *otherPoint) {
    return x == otherPoint->x && y == otherPoint->y && z == otherPoint->z;
}

void Point::applyHomothetyInX(float scale, Point *point) {
    this->x = (float)(point->x) + scale * (float)(this->x - point->x);
}
