//
// Created by axel on 25/11/19.
//

#ifndef GAME_COLLITIONBOX_H
#define GAME_COLLITIONBOX_H

#include <list>
#include "../../components/Point.h"
#include "../../../net/messaging/Sendable.h"

class ScreenPosition;
class Entity;
class CollitionBox {

public:
    CollitionBox(int centerX, int centerY, int centerZ, int w, int h, int d, int id, bool visual);
    ~CollitionBox();

    bool intersectsWith(CollitionBox* collitionBox);
    void moveBy(int xAmount, int yAmount, int zAmount);
    void dragToRight(int amount);
    bool notArrivedAt(Point* destination);
    void moveOneUnitInTheDirectionOf(Point* destination);
    bool hasInsideItsVolume(Point* corner);
    Entity* getOwner();
    void setOwner(Entity* owner);

    bool isVisual() {
        return visual;
    }

    int getX(){
        return center->x;
    }

    int getY(){
        return center->y;
    }

    int getZ(){
        return center->z;
    }

    int getID(){
        return id;
    }

    Sendable *generateSendable();
    void setScreenPosition(ScreenPosition *screenPosition);
    void moveBy(Point delta);
    void restorePreviousPosition();

protected:
    bool anyCornerIntersectsWith(CollitionBox* collitionBox);

private:
    bool visual = false;
    Point* center = nullptr;
    list<Point*> candidateMoves;

    ScreenPosition* screenPosition = nullptr;

    void calculateAndAssignCorners(int centerX, int centerY, int centerZ);
    void calculateCandidates();

    std::list<Point*> corners;
    Entity* owner = nullptr;
    int id;
    int w;
    int h;
    int d;
};


#endif //GAME_COLLITIONBOX_H
