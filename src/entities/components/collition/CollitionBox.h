//
// Created by axel on 25/11/19.
//

#ifndef GAME_COLLITIONBOX_H
#define GAME_COLLITIONBOX_H


#include "../../entityHierarchy/Entity.h"
#include "../../components/Point.h"

class CollitionBox {

public:
    CollitionBox(int x, int y, int z, int w, int h, int d, int id);
    ~CollitionBox()

    void setOwner(Entity* owner);
    bool intersectsWith(CollitionBox* collitionBox, Point* corrected);

    Entity* getOwner(){
        return owner;
    }

    int getID(){
        return id;
    }

private:
    bool cornerIntersectsWith(CollitionBox* collitionBox, Point* corner);
    bool anyCornerIntersectsWith(CollitionBox* collitionBox);
    bool hasInsideItsVolume(Point* corner);
    void calculateAndAssignCorners(int x, int y, int z);

    list<Point*> corners;
    Entity* owner = nullptr;
    int id;

    int DEFAULT_WIDTH = 10;
    int DEFAULT_HEIGHT = 10;
    int DEFAULT_DEPTH = 10;
    int DEFAULT_NULL_ID = -1;   //es la id que tienen todos los colition box que no estan//trackeados por el CollitionManager

    int w;
    int h;
    int d;

    void setOwner(Entity *owner);
};


#endif //GAME_COLLITIONBOX_H
