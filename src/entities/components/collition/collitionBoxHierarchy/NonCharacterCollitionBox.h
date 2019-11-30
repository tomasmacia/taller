//
// Created by axelmpm on 30/11/19.
//

#ifndef GAME_NONCHARACTERCOLLITIONBOX_H
#define GAME_NONCHARACTERCOLLITIONBOX_H


#include "BlockingCollitionBox.h"

class NonCharacterCollitionBox : public BlockingCollitionBox{

public:
    NonCharacterCollitionBox(int i, int i1, int i2, int i3, int i4, int i5, int i6, Entity *pEntity);
};


#endif //GAME_NONCHARACTERCOLLITIONBOX_H
