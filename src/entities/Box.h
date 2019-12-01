//
// Created by axel on 24/11/19.
//

#ifndef GAME_BOX_H
#define GAME_BOX_H


#include "entityHierarchy/Utillity.h"

class Box  : public Utillity{

    int setAttackedWith(AttackCode attack) override ;
};


#endif //GAME_BOX_H
