//
// Created by axel on 28/11/19.
//

#ifndef GAME_WEAPON_H
#define GAME_WEAPON_H


#include "UnanimatedEntity.h"
#include "../Life.h"


class Weapon : public UnanimatedEntity{

public:
    Weapon(Life* life);

    virtual int useOn(Entity* entity) = 0;
    bool broke();

protected:
    int USES_AMOUNT = 3;
};



#endif //GAME_WEAPON_H
