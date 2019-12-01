//
// Created by axel on 25/11/19.
//

#ifndef GAME_COLLITIONBOX_H
#define GAME_COLLITIONBOX_H


#include "../../entityHierarchy/Entity.h"

class CollitionBox {

public:
    CollitionBox(int x, int y, int z, int w, int h, int d, int id);

    void setOwner(Entity* owner);
    bool intersectsWith(CollitionBox* collitionBox);

    int x;
    int y;
    int z;
    int w;
    int h;
    int d;
    int id;
    Entity* owner = nullptr;

private:
    bool hasInsideItsVolumeThePositionPointOf(CollitionBox* collitionBox);

    int DEFAULT_WIDTH = 10;
    int DEFAULT_HEIGHT = 10;
    int DEFAULT_DEPTH = 10;
    int DEFAULT_NULL_ID = -1;   //es la id que tienen todos los colition box que no estan
                                //trackeados por el CollitionManager
};


#endif //GAME_COLLITIONBOX_H
