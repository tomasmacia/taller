//
// Created by axelmpm on 30/11/19.
//

#ifndef GAME_CHARACTERCOLLITIONBOX_H
#define GAME_CHARACTERCOLLITIONBOX_H


#include "BlockingCollitionBox.h"
#include "../../../Character.h"

class CharacterCollitionBox : public  BlockingCollitionBox{

public:
    CharacterCollitionBox(int i, int i1, int i2, int i3, int i4, int i5, int i6, Character *pCharacter);
};


#endif //GAME_CHARACTERCOLLITIONBOX_H
