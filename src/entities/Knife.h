//
// Created by axel on 24/11/19.
//

#ifndef GAME_KNIFE_H
#define GAME_KNIFE_H


#include "entityHierarchy/Weapon.h"

class Knife : public Weapon{

    int useOn(Entity* entity) override ;
};


#endif //GAME_KNIFE_H
