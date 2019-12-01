//
// Created by axel on 28/11/19.
//

#ifndef GAME_WEAPON_H
#define GAME_WEAPON_H


#include "InanimatedEntity.h"
#include "../Life.h"


class Weapon : public InanimatedEntity{

public:
    Weapon(Life* life);

    virtual int useOn(Entity* entity) = 0;
    bool broke();

private:
    Life* life = nullptr;
};



#endif //GAME_WEAPON_H
