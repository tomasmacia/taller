//
// Created by axelmpm on 2/12/19.
//

#ifndef GAME_POINT_H
#define GAME_POINT_H


class Point {

public:
    Point(int x, int y, int z);

    void moveBy(int xAmount, int yAmount, int zAmount);
    void moveBy(Point delta);
    void plus(Point delta);
    int distanceWith(Point* other);
    int distanceTo(Point* other);
    void save();
    void restore();
    Point delta();
    Point minus(Point* other);
    Point oposite();
    bool isZero();
    void setAt(Point *pPoint);
    bool coincidesWith(Point *otherPoint);
    void applyHomothetyInX(float scale, Point *point);

    int savedX;
    int savedY;
    int savedZ;

    int x;
    int y;
    int z;
};


#endif //GAME_POINT_H
