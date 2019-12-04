//
// Created by axel on 25/11/19.
//

#ifndef GAME_COLLITIONBOX_H
#define GAME_COLLITIONBOX_H


#include "../../components/Point.h"

class Entity;
class CollitionBox {

public:
    CollitionBox(int x, int y, int z, int w, int h, int d, int id);
    ~CollitionBox();

    void setOwner(Entity* owner);
    bool intersectsWith(CollitionBox* collitionBox);
    void moveAllCornersBy(int xAmount, int yAmount, int zAmount);
    void dragToRight(int amount);
    bool notArrivedAt(Point* destination);
    void moveOneUnitInTheDirectionOf(Point* destination);
    bool hasInsideItsVolume(Point* corner);
    void savePreviousPosition();
    void restorePreviousPosition();

    int getX(){
        return corners.front()->x;
    }

    int getY(){
        return corners.front()->y;
    }

    int getZ(){
        return corners.front()->z;
    }

    Entity* getOwner(){
        return owner;
    }

    int getID(){
        return id;
    }
private:
    Point* previousPosition = nullptr;

    bool cornerIntersectsWith(CollitionBox* collitionBox, Point* corner);
    bool anyCornerIntersectsWith(CollitionBox* collitionBox);

    void calculateAndAssignCorners(int x, int y, int z);
    list<Point*> corners;
    Entity* owner = nullptr;

    int id;

    int w;
    int h;
    int d;
};


#endif //GAME_COLLITIONBOX_H
