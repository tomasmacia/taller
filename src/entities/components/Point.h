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
    void save();
    void restore();

    int savedX;
    int savedY;
    int savedZ;

    int x;
    int y;
    int z;

    void setAt(int x, int y, int z);

    Point delta();

    Point oposite();
};


#endif //GAME_POINT_H
