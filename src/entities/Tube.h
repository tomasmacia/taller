//
// Created by axel on 24/11/19.
//

#ifndef GAME_TUBE_H
#define GAME_TUBE_H


#include "entityHierarchy/Weapon.h"

class Tube : public Weapon{

public:
    int useOn(Entity* entity) override ;
};


#endif //GAME_TUBE_H
