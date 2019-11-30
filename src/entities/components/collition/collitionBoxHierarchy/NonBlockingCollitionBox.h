//
// Created by axelmpm on 30/11/19.
//

#ifndef GAME_NONBLOCKINGCOLLITIONBOX_H
#define GAME_NONBLOCKINGCOLLITIONBOX_H

#include "CollitionBox.h"

class NonBlockingCollitionBox : public CollitionBox{

public:
    NonBlockingCollitionBox(int i, int i1, int i2, int i3, int i4, int i5, int i6, Entity *pEntity);
};


#endif //GAME_NONBLOCKINGCOLLITIONBOX_H
