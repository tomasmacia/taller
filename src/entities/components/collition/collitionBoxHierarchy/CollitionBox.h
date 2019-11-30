//
// Created by axel on 25/11/19.
//

#ifndef GAME_COLLITIONBOX_H
#define GAME_COLLITIONBOX_H


#include "../../../entityHierarchy/Entity.h"

class CollitionBox {

public:
    CollitionBox(int x, int y, int z, int w, int h, int d, int id, Entity* owner);

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
};


#endif //GAME_COLLITIONBOX_H
