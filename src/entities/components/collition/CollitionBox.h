//
// Created by axel on 25/11/19.
//

#ifndef GAME_COLLITIONBOX_H
#define GAME_COLLITIONBOX_H

#include <list>
#include "../../components/Point.h"

class Entity;
class CollitionBox {

public:
    CollitionBox(int x, int y, int z, int w, int h, int d, int id);
    ~CollitionBox();

    bool intersectsWith(CollitionBox* collitionBox);
    void moveAllCornersBy(int xAmount, int yAmount, int zAmount);
    void dragToRight(int amount);
    bool notArrivedAt(Point* destination);
    void moveOneUnitInTheDirectionOf(Point* destination);
    bool hasInsideItsVolume(Point* corner);
    void savePreviousPosition();
    void restorePreviousPosition();
    Entity* getOwner();
    void setOwner(Entity* owner);

    int getX(){
        return corners.front()->x;
    }

    int getY(){
        return corners.front()->y;
    }

    int getZ(){
        return corners.front()->z;
    }

    int getID(){
        return id;
    }

protected:
    bool anyCornerIntersectsWith(CollitionBox* collitionBox);

private:
    Point* previousPosition = nullptr;
    bool cornerIntersectsWith(CollitionBox* collitionBox, Point* corner);
    void calculateAndAssignCorners(int x, int y, int z);

    std::list<Point*> corners;

    Entity* owner = nullptr;

    int id;
    int w;
    int h;
    int d;
};


#endif //GAME_COLLITIONBOX_H
