//
// Created by axel on 25/11/19.
//

#ifndef GAME_COLLITIONBOX_H
#define GAME_COLLITIONBOX_H


#include "../../Character.h"

class CollitionBox {

public:
    CollitionBox(int x, int y, int z, int w, int h, int d, int id, Character* owner);

    void tryPos(int tryX, int tryY, int tryZ);
    void resetPos();
    bool intersectsWith(CollitionBox* collitionBox);

    int stashedX{};
    int stashedY{};
    int stashedZ{};

    int x;
    int y;
    int z;
    int w;
    int h;
    int d;
    int id;
    Character* owner = nullptr;

private:
    bool hasInsideItsVolumeThePositionPointOf(CollitionBox* collitionBox);
};


#endif //GAME_COLLITIONBOX_H
