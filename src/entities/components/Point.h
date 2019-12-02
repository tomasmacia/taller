//
// Created by axelmpm on 2/12/19.
//

#ifndef GAME_POINT_H
#define GAME_POINT_H


class Point {

public:
    Point(int x, int y, int z);

    void moveBy(int xAmount, int yAmount, int zAmount);

    int x;
    int y;
    int z;
};


#endif //GAME_POINT_H
